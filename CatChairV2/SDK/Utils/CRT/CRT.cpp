#include "CRT.hpp"
#include <cstdint>

unsigned int Crt::wcslen(const wchar_t* str) {
	int counter = 0;
	if (!str)
		return 0;
	for (; *str != '\0'; ++str)
		++counter;
	return counter;
}

int Crt::wcsicmp_insensitive(const wchar_t* cs, const wchar_t* ct) {
	const auto len = wcslen(cs);
	if (len != wcslen(ct))
		return false;

	for (size_t i = 0; i < len; i++)
		if ((cs[i] | L' ') != (ct[i] | L' '))
			return false;

	return true;
}

bool Crt::strcmp(const char* a, const char* b) {
	if ((uintptr_t)a == 0x00000000ffffffff || (uintptr_t)b == 0x00000000ffffffff)
		return false;
	if ((uintptr_t)a == 0x000000000000007d || (uintptr_t)b == 0x000000000000007d)
		return false;

	if (!a || !b)
		return !a && !b;

	int ret = 0;
	unsigned char* p1 = (unsigned char*)a;
	unsigned char* p2 = (unsigned char*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	return ret == 0;
}

const Crt::module_t Crt::ModuleBase(const wchar_t* name)
{

	const nt::peb* peb = reinterpret_cast<nt::peb*>(__readgsqword(0x60));
	if (!peb)
		return {}; // how the fuck did we even get here?

	const nt::list_entry head = peb->Ldr->InMemoryOrderModuleList;

	for (auto curr = head; curr.Flink != &peb->Ldr->InMemoryOrderModuleList; curr = *curr.Flink)
	{
		nt::ldr_data_table_entry* mod = reinterpret_cast<nt::ldr_data_table_entry*>(contains_record(curr.Flink, nt::ldr_data_table_entry, InMemoryOrderLinks));

		if (mod->BaseDllName.Buffer)
		{
			if (wcsicmp_insensitive(mod->BaseDllName.Buffer, name))
			{
				return { mod->DllBase, mod->BaseDllName.Buffer, mod->SizeOfImage };
			}
		}
	}

	return {};
}

const void* Crt::IL2CppExport(const char* function)
{
	auto module = ModuleBase(L"GameAssembly.dll");
	if (!module.base)
		return {};

	const auto base = reinterpret_cast<uintptr_t>(module.base);
	const nt::image_dos_header* dos_header = reinterpret_cast<nt::image_dos_header*>(base);
	const nt::image_nt_headers* nt_header = reinterpret_cast<nt::image_nt_headers*>(base + dos_header->e_lfanew);

	const nt::image_data_directory* data_directory = reinterpret_cast<const nt::image_data_directory*>(&nt_header->OptionalHeader.DataDirectory[0]);
	const nt::image_export_directory* image_export_directory = reinterpret_cast<nt::image_export_directory*>(base + data_directory->VirtualAddress);

	const auto* const rva_table = reinterpret_cast<const unsigned long*>(base + image_export_directory->AddressOfFunctions);
	const auto* const ord_table = reinterpret_cast<const unsigned short*>(base + image_export_directory->AddressOfNameOrdinals);

	if (image_export_directory)
	{
		for (unsigned int idx{ 0 }; idx < image_export_directory->NumberOfNames; idx++)
		{
			const auto fn_name = reinterpret_cast<const char*>(base + reinterpret_cast<const unsigned long*>(base + image_export_directory->AddressOfNames)[idx]);

			if (strcmp(fn_name, function))
				return reinterpret_cast<void*>(base + ((uint32_t*)(base + image_export_directory->AddressOfFunctions))[ord_table[idx]]);
		}
	}

	return { };
}
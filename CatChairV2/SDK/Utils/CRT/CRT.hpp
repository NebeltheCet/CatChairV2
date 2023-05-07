#pragma once

#include <intrin.h>

#undef min
#undef max
#define max( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#define min( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )

namespace Crt {
#define contains_record( address, type, field ) ( ( type* )( ( char* )( address ) - ( uintptr_t )( & ( (type* ) 0 ) -> field ) ) )
#define loword(l) ((uint16_t)(((uintptr_t)(l)) & 0xffff))

	unsigned int wcslen(const wchar_t* str);
	int wcsicmp_insensitive(const wchar_t* cs, const wchar_t* ct);
	bool strcmp(const char* a, const char* b);

	struct module_t
	{
		void* base;
		const wchar_t* name;
		size_t size;
		module_t(void* b, const wchar_t* n, size_t s) : base(b), name(n), size(s) {}
		module_t() : base(0), name(L""), size(0) {}
	};

	namespace nt
	{
		struct list_entry
		{
			struct list_entry* Flink;
			struct list_entry* Blink;
		};

		struct unicode_string
		{
			unsigned short Length;
			unsigned short MaximumLength;
			wchar_t* Buffer;
		};

		struct peb_ldr_data
		{
			unsigned long Length;
			unsigned long Initialized;
			const char* SsHandle;
			list_entry InLoadOrderModuleList;
			list_entry InMemoryOrderModuleList;
			list_entry InInitializationOrderModuleList;
		};

		struct peb
		{
			unsigned char   Reserved1[2];
			unsigned char   BeingDebugged;
			unsigned char   Reserved2[1];
			const char* Reserved3[2];
			peb_ldr_data* Ldr;
		};

		struct ldr_data_table_entry
		{
			list_entry InLoadOrderModuleList;
			list_entry InMemoryOrderLinks;
			list_entry InInitializationOrderModuleList;
			void* DllBase;
			void* EntryPoint;
			union {
				unsigned long SizeOfImage;
				const char* _dummy;
			};
			unicode_string FullDllName;
			unicode_string BaseDllName;
		};

		struct image_dos_header
		{
			unsigned short e_magic;
			unsigned short e_cblp;
			unsigned short e_cp;
			unsigned short e_crlc;
			unsigned short e_cparhdr;
			unsigned short e_minalloc;
			unsigned short e_maxalloc;
			unsigned short e_ss;
			unsigned short e_sp;
			unsigned short e_csum;
			unsigned short e_ip;
			unsigned short e_cs;
			unsigned short e_lfarlc;
			unsigned short e_ovno;
			unsigned short e_res[4];
			unsigned short e_oemid;
			unsigned short e_oeminfo;
			unsigned short e_res2[10];
			long e_lfanew;
		};

		struct image_file_header
		{
			unsigned short Machine;
			unsigned short NumberOfSections;
			unsigned long TimeDateStamp;
			unsigned long PointerToSymbolTable;
			unsigned long NumberOfSymbols;
			unsigned short SizeOfOptionalHeader;
			unsigned short Characteristics;
		};

		struct image_export_directory
		{
			unsigned long Characteristics;
			unsigned long TimeDateStamp;
			unsigned short MajorVersion;
			unsigned short MinorVersion;
			unsigned long Name;
			unsigned long Base;
			unsigned long NumberOfFunctions;
			unsigned long NumberOfNames;
			unsigned long AddressOfFunctions;
			unsigned long AddressOfNames;
			unsigned long AddressOfNameOrdinals;
		};

		struct image_data_directory
		{
			unsigned long VirtualAddress;
			unsigned long Size;
		};

		struct image_optional_header
		{
			unsigned short Magic;
			unsigned char MajorLinkerVersion;
			unsigned char MinorLinkerVersion;
			unsigned long SizeOfCode;
			unsigned long SizeOfInitializedData;
			unsigned long SizeOfUninitializedData;
			unsigned long AddressOfEntryPoint;
			unsigned long BaseOfCode;
			unsigned long long ImageBase;
			unsigned long SectionAlignment;
			unsigned long FileAlignment;
			unsigned short MajorOperatingSystemVersion;
			unsigned short MinorOperatingSystemVersion;
			unsigned short MajorImageVersion;
			unsigned short MinorImageVersion;
			unsigned short MajorSubsystemVersion;
			unsigned short MinorSubsystemVersion;
			unsigned long Win32VersionValue;
			unsigned long SizeOfImage;
			unsigned long SizeOfHeaders;
			unsigned long CheckSum;
			unsigned short Subsystem;
			unsigned short DllCharacteristics;
			unsigned long long SizeOfStackReserve;
			unsigned long long SizeOfStackCommit;
			unsigned long long SizeOfHeapReserve;
			unsigned long long SizeOfHeapCommit;
			unsigned long LoaderFlags;
			unsigned long NumberOfRvaAndSizes;
			image_data_directory DataDirectory[16];
		};

		struct image_nt_headers {
			unsigned long Signature;
			image_file_header FileHeader;
			image_optional_header OptionalHeader;
		};
	}

	const module_t ModuleBase(const wchar_t* name);
	const void* IL2CppExport(const char* function);
}
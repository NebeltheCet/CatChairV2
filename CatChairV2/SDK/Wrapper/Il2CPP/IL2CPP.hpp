#pragma once
#include "../../Utils/CRT/CRT.hpp"
#include <cstdint>

#define CLASS( nameSpace, className ) static Il2CppClass* StaticClass()										\
									  {																		 \
										return Il2CppWrapper::GetClassFromName(nameSpace, className);         \
									  }	                                                                       																	

#define STATIC_MEMBER( type, name ) static type & name( ) { static auto field_##name = uintptr_t( StaticClass( )->GetFieldFromName( #name ) ); return *reinterpret_cast< type* >( field_##name ); }
#define METHOD( type, name ) static auto name = *reinterpret_cast< type >( StaticClass( )->GetMethodFromName( #name ) );																	   
#define MEMBER( type, name ) type & name( ) { static uintptr_t name = StaticClass( )->GetFieldFromName( #name, true ); return *reinterpret_cast< type* >( this + name ); }

class Il2CppField {
public:
	Il2CppField* il2cpp_field_get_offset()
	{
		static auto il2cpp_field_get_offset = reinterpret_cast<Il2CppField * (*)(Il2CppField*)>(Crt::IL2CppExport("il2cpp_field_get_offset"));
		return il2cpp_field_get_offset(this);
	}

	const char* il2cpp_field_get_name()
	{
		static auto il2cpp_field_get_name = reinterpret_cast<const char* (*)(Il2CppField*)>(Crt::IL2CppExport("il2cpp_field_get_name"));
		return il2cpp_field_get_name(this);
	}

	Il2CppField* il2cpp_field_static_get_value(uintptr_t* i)
	{
		static auto il2cpp_field_static_get_value = reinterpret_cast<Il2CppField * (*)(Il2CppField*, uintptr_t*)>(Crt::IL2CppExport("il2cpp_field_static_get_value"));
		return il2cpp_field_static_get_value(this, i);
	}
};

class Il2CppMethod {
public:
	char* pad001[0xC];
	const char* name;
	char* pad002[0x8];
	uintptr_t parameters;

	int il2cpp_method_get_param_count()
	{
		static auto il2cpp_method_get_param_count = reinterpret_cast<int (*)(Il2CppMethod*)>(Crt::IL2CppExport("il2cpp_method_get_param_count"));
		return il2cpp_method_get_param_count(this);
	}

	const char* il2cpp_method_get_param_name(uint32_t index)
	{
		static auto il2cpp_method_get_param_name = reinterpret_cast<const char* (*)(Il2CppMethod*, uint32_t)>(Crt::IL2CppExport("il2cpp_method_get_param_name"));
		return il2cpp_method_get_param_name(this, index);
	}

	const char* il2cpp_method_get_name()
	{
		static auto il2cpp_method_get_name = reinterpret_cast<const char* (*)(Il2CppMethod*)>(Crt::IL2CppExport("il2cpp_method_get_name"));
		return il2cpp_method_get_name(this);
	}
};

class Il2CppType {
public:
	Il2CppType* il2cpp_type_get_object()
	{
		static auto il2cpp_type_get_object = reinterpret_cast<Il2CppType * (*)(Il2CppType*)>(Crt::IL2CppExport(__func__));
		return il2cpp_type_get_object(this);
	}
};

class Il2CppObject {
public:

};

class Il2CppClass : public Il2CppObject {
private:
	Il2CppField* il2cpp_class_get_fields(uintptr_t* iter)
	{
		static auto il2cpp_class_get_fields = reinterpret_cast<Il2CppField * (*)(Il2CppClass*, uintptr_t*)>(Crt::IL2CppExport("il2cpp_class_get_fields"));
		return il2cpp_class_get_fields(this, iter);
	}

	Il2CppMethod* il2cpp_class_get_methods(uintptr_t* iter)
	{
		static auto il2cpp_class_get_methods = reinterpret_cast<Il2CppMethod * (*)(Il2CppClass*, uintptr_t*)>(Crt::IL2CppExport("il2cpp_class_get_methods"));
		return il2cpp_class_get_methods(this, iter);
	}

	Il2CppField* FieldInternal(const char* name, bool offset = true)
	{
		uintptr_t iterator = uintptr_t();

		while (Il2CppField* field = il2cpp_class_get_fields(&iterator))
		{
			const char* field_name = field->il2cpp_field_get_name();
			if (!field_name)
				break;

			if (!Crt::strcmp(field_name, name))
				continue;

			if (!offset)
				return field;

			printf("%s[0x%p]\n", name, (uintptr_t)field->il2cpp_field_get_offset());
			return field->il2cpp_field_get_offset();
		}

		return { };
	}
public:
	Il2CppClass* parent()
	{
		return *reinterpret_cast<Il2CppClass**>(this + 0x58);
	}

	uintptr_t static_fields()
	{
		return *reinterpret_cast<uintptr_t*>(this + 0xB8);
	}

	Il2CppType* il2cpp_class_get_type()
	{
		static auto il2cpp_class_get_type = reinterpret_cast<Il2CppType * (*)(Il2CppClass*)>(Crt::IL2CppExport("il2cpp_class_get_type"));
		return il2cpp_class_get_type(this);
	}

	Il2CppMethod* GetMethodFromName(const char* name, int arg_count = -1, const char* arg_name = "", int selected_arg = -1)
	{
		uintptr_t iterator = uintptr_t();
		while (Il2CppMethod* method = il2cpp_class_get_methods(&iterator)) {
			const char* method_name = method->il2cpp_method_get_name();
			if (Crt::strcmp(method_name, name))
			{
				int param_count = method->il2cpp_method_get_param_count();

				if (arg_count >= 0 && param_count != arg_count)
					continue;

				if (selected_arg >= 0 && arg_name)
				{
					uintptr_t args = method->parameters;

					if (selected_arg > param_count)
						continue;

					char* param_name;

					if (param_count > 0)
						param_name = (char*)method->il2cpp_method_get_param_name(selected_arg - 1);
					else
						param_name = (char*)("-");

					if (!param_name || !Crt::strcmp(param_name, arg_name))
						continue;
				}

				printf("%s[0x%p]\n", method_name, (uintptr_t)method);
				return method;
			}

		}

		return { };
	}

	uintptr_t GetFieldFromName(const char* name, bool offset = true)
	{
		if (offset)
			return uintptr_t(FieldInternal(name));

		Il2CppField* field = FieldInternal(name, false);

		uintptr_t ret{ };
		field->il2cpp_field_static_get_value(&ret);
		return ret;
	}
};

class Il2CppString {
public:
	decltype(auto) il2cpp_string_new()
	{

	}
};

class Il2CppImage {
public:
	decltype(auto) il2cpp_class_from_name(const char* name_space, const char* klass)
	{
		static auto il2cpp_class_from_name = reinterpret_cast<Il2CppClass * (*)(Il2CppImage*, const char*, const char*)>(Crt::IL2CppExport("il2cpp_class_from_name"));
		return il2cpp_class_from_name(this, name_space, klass);
	}
};

class Il2CppAssemblies {
public:

	decltype(auto) il2cpp_assembly_get_image()
	{
		static auto il2cpp_assembly_get_image = reinterpret_cast<Il2CppImage * (*)(Il2CppAssemblies*)>(Crt::IL2CppExport(__func__));
		return il2cpp_assembly_get_image(this);
	}
};

class Il2CppDomain {
public:
	decltype(auto) il2cpp_domain_get_assemblies(uintptr_t* list)
	{
		static auto il2cpp_domain_get_assemblies = reinterpret_cast<Il2CppAssemblies * *(*)(Il2CppDomain*, uintptr_t*)>(Crt::IL2CppExport(__func__));
		return il2cpp_domain_get_assemblies(this, list);
	}

	static decltype(auto) il2cpp_domain_get()
	{
		static auto il2cpp_domain_get = reinterpret_cast<Il2CppDomain * (*)()>(Crt::IL2CppExport("il2cpp_domain_get"));
		return il2cpp_domain_get();
	}
};

class Il2CppWrapper {
public:
	static decltype(auto) ThreadAttach()
	{
		static auto il2cpp_thread_attach = reinterpret_cast<void(*)()>(Crt::IL2CppExport("il2cpp_thread_attach"));
		il2cpp_thread_attach();
		printf("Attached Il2Cpp Thread\n");
	}

	template< typename t >
	static decltype(auto) il2cpp_object_new(void* object)
	{
		static auto il2cpp_object_new = reinterpret_cast<t(*)(void*)>(Crt::IL2CppExport(__func__));
		return il2cpp_object_new(object);
	}

	static Il2CppClass* GetClassFromName(const char* nameSpace, const char* className)
	{
		Il2CppDomain* domain = Il2CppDomain::il2cpp_domain_get();

		uint64_t assembly_count = uint64_t();
		Il2CppAssemblies** assemblies = domain->il2cpp_domain_get_assemblies(&assembly_count);
		for (size_t idx{ 0 }; idx < assembly_count; idx++)
		{
			Il2CppImage* image = assemblies[idx]->il2cpp_assembly_get_image();
			if (!image)
				continue;

			Il2CppClass* klass = image->il2cpp_class_from_name(nameSpace, className); /* should be the Instance Offset -> Class Offset */
			if (!klass)
				continue;

			printf("%s::%s[0x%p]\n", nameSpace, className, (uintptr_t)klass);
			return klass;
		}

		return {};
	}

	static void* GetTypeObject(const char* nameSpace, const char* className)
	{
		Il2CppClass* klass = GetClassFromName(nameSpace, className);
		if (!klass)
			return { };

		return klass->il2cpp_class_get_type()->il2cpp_type_get_object();
	}
};
#pragma once
#include <windows.h>
#include <string>

#define CREATE_TYPE( type, name, args ) typedef type( __cdecl* name) args; name _##name;
#define ASSIGN_TYPE( name ) _##name = (name)GetProcAddress(LoadLibraryW(L"GameAssembly.dll"), #name);

namespace il2cpp_lib {
	inline void* root_domain;
	inline void* base_image;
	inline void* base_assembly;

	CREATE_TYPE(void*, il2cpp_domain_get, ());
	CREATE_TYPE(char*, il2cpp_field_get_name, (void* field));
	CREATE_TYPE(void*, il2cpp_class_get_field_from_name, (void* klass, const char* name));
	CREATE_TYPE(std::uint32_t, il2cpp_field_get_offset, (void* field));
	CREATE_TYPE(void, il2cpp_field_static_get_value, (void* field, std::uintptr_t* value));
	CREATE_TYPE(void*, il2cpp_domain_assembly_open, (void* domain, const char* name));
	CREATE_TYPE(void*, il2cpp_class_get_fields, (void* klass, void** iterator));
	CREATE_TYPE(void, il2cpp_thread_attach, (void* domain));
	CREATE_TYPE(void*, il2cpp_assembly_get_image, (void* assembly));
	CREATE_TYPE(void*, il2cpp_class_from_name, (void* image, const char* name_space, const char* klass));
	CREATE_TYPE(void*, il2cpp_field_get_type, (void* field));
	CREATE_TYPE(void*, il2cpp_class_get_method_from_name, (void* klass, const char* name, int param_count));
	CREATE_TYPE(int, il2cpp_method_get_param_count, (void* method));
	CREATE_TYPE(void*, il2cpp_method_get_name, (void* method));
	CREATE_TYPE(void*, il2cpp_class_get_methods, (void* klass, void** iterator));

	inline auto think(const char* assembly_name) -> bool {
		ASSIGN_TYPE(il2cpp_domain_get);
		ASSIGN_TYPE(il2cpp_field_get_name);
		ASSIGN_TYPE(il2cpp_class_get_field_from_name);
		ASSIGN_TYPE(il2cpp_field_get_offset);
		ASSIGN_TYPE(il2cpp_field_static_get_value);
		ASSIGN_TYPE(il2cpp_domain_assembly_open);
		ASSIGN_TYPE(il2cpp_class_get_fields);
		ASSIGN_TYPE(il2cpp_thread_attach);
		ASSIGN_TYPE(il2cpp_assembly_get_image);
		ASSIGN_TYPE(il2cpp_class_from_name);
		ASSIGN_TYPE(il2cpp_field_get_type);
		ASSIGN_TYPE(il2cpp_class_get_method_from_name);
		ASSIGN_TYPE(il2cpp_method_get_param_count);
		ASSIGN_TYPE(il2cpp_method_get_name);
		ASSIGN_TYPE(il2cpp_class_get_methods);

		root_domain = _il2cpp_domain_get();
		_il2cpp_thread_attach(root_domain);

		base_assembly = _il2cpp_domain_assembly_open(root_domain, assembly_name);
		base_image = _il2cpp_assembly_get_image(base_assembly);

		printf("[+] initialized\n");
		return true;
	}
	inline auto dump_methods(const char* _namespace, const char* class_name) -> void {
		void* iterator = NULL;
		const auto il2cpp_class = _il2cpp_class_from_name(base_image, _namespace, class_name);

		while (auto method = _il2cpp_class_get_methods(il2cpp_class, &iterator)) {
			printf("[~] dumped %s::%s: 0x%x\n", class_name, (char*)_il2cpp_method_get_name(method), 69420/*to-do*/);
		}
	}
	inline auto dump_fields(const char* _namespace, const char* class_name) -> void {
		void* iterator = NULL;
		const auto il2cpp_class = _il2cpp_class_from_name(base_image, _namespace, class_name);

		while (auto field = _il2cpp_class_get_fields(il2cpp_class, &iterator)) {
			printf("[~] dumped %s::%s: 0x%x\n", class_name, _il2cpp_field_get_name(field), _il2cpp_field_get_offset(field));
		}
	}
}
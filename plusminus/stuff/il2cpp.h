namespace il2cpp {
	typedef int(__stdcall* GPC)(DWORD64);
	typedef DWORD64(__stdcall* AGI)(DWORD64);
	typedef DWORD64(__stdcall* New)(DWORD64);
	typedef DWORD64(__stdcall* Dm)();
	typedef DWORD64(__stdcall* CFN)(DWORD64, const char*, const char*);
	typedef DWORD64(__stdcall* Call)(DWORD64, DWORD64);
	typedef DWORD64(__stdcall* Ptr)(DWORD64, DWORD64*);
	typedef DWORD64* (__cdecl* DGA)(void* domain, DWORD64* size);

	Ptr class_get_methods = 0;
	Ptr class_get_fields = 0;
	Dm domain_get = 0;
	DGA domain_get_assemblies = 0;
	AGI assembly_get_image = 0;
	New new_class_instance = 0;
	CFN class_from_name = 0;
	AGI field_get_offset = 0;
	Ptr field_static_get_value = 0;
	GPC method_get_param_count = 0;
	Call array_new = 0;

	static void InitIL() {
		method_get_param_count = (GPC)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_method_get_param_count")));
		field_static_get_value = (Ptr)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_field_static_get_value")));
		field_get_offset = (AGI)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_field_get_offset")));
		class_from_name = (CFN)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_class_from_name")));
		assembly_get_image = (AGI)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_assembly_get_image")));
		new_class_instance = (New)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_object_new")));
		domain_get_assemblies = (DGA)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_domain_get_assemblies")));
		domain_get = (Dm)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_domain_get")));
		class_get_fields = (Ptr)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_class_get_fields")));
		class_get_methods = (Ptr)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_class_get_methods")));
		array_new = (Call)(GetExport(GetModBase(xorstr(L"GameAssembly.dll")), xorstr("il2cpp_array_new")));
	}
}

DWORD64 il2cpp_array(DWORD64 klass, DWORD64 size) {
	DWORD64 arr = il2cpp::array_new(klass, size);
	return arr;
}
DWORD64 il2cpp_object_new(DWORD64 klass) {
	DWORD64 objnew = il2cpp::new_class_instance(klass);
	//printf("il2cpp_object_new: %s\n", std::to_string(objnew));
	return objnew;
}
void il2cpp_hook(DWORD64 method, PVOID hook, PDWORD64 ret) {
	DWORD64 orig = read(method, DWORD64);
	if (orig != method) write(ret, orig, DWORD64); //we dont override original pointer
	write(method, hook, PVOID);
}
DWORD64 il2cpp_field(DWORD64 klass, const char* nm, bool alwaysfalse = false) {
	DWORD64 iter = 0;
	DWORD64 f;
	while (f = il2cpp::class_get_fields(klass, &iter)) {
		char* name = (char*)read(f, DWORD64);
		if (!name) break;
		if (!m_strcmp(name, (char*)nm)) {
			continue;
		}
		if (alwaysfalse) {
			return f;
		}
		DWORD64 offset = il2cpp::field_get_offset(f);
		return offset;
	}
	return 0;
}
DWORD64 il2cpp_value(DWORD64 klass, const char* name) {
	DWORD64 fl = il2cpp_field(klass, name, true);
	DWORD64 tt = 0;
	DWORD64 _t = il2cpp::field_static_get_value(fl, &tt);
	return tt;
}
DWORD64 il2cpp_method(DWORD64 kl, const char* name, int arg = -1, const char* aname = "", int totalarg = -1) {
	DWORD64 iter = 0;
	DWORD64 f;
	while (f = il2cpp::class_get_methods(kl, &iter)) {
		char* st = (char*)read(f + 0x10, DWORD64);
		if (m_strcmp(st, (char*)name)) {
			if (arg >= 0 && aname) {
				DWORD64 args = read(f + 0x28, DWORD64);
				int method_count = il2cpp::method_get_param_count(f);
				if (arg > method_count || (totalarg >= 0 && method_count != totalarg)) continue;
				char* argname;
				if (method_count > 0) {
					argname = (char*)read(args + (arg - 1) * 0x18, DWORD64);
				}
				else argname = (char*)"-";
				if (!argname || !m_strcmp(argname, (char*)aname)) continue;
			}
			return f;
		}
	}
	return 0;
}
DWORD64 InitClass(const char* name, const char* ns = "") {
	DWORD64 domain = il2cpp::domain_get();
	DWORD64 nrofassemblies = 0;
	DWORD64* assemblies;
	assemblies = il2cpp::domain_get_assemblies((void*)domain, &nrofassemblies);
	for (int i = 0; i < nrofassemblies; i++) {
		DWORD64 img = il2cpp::assembly_get_image(assemblies[i]);
		DWORD64 kl = il2cpp::class_from_name(img, ns, name);
		if (!kl) continue;
		return kl;
	}
	return 0;
}
#define CLASS InitClass
#define METHOD(...) read(il2cpp_method(__VA_ARGS__), DWORD64)
#define OFFSET il2cpp_field
namespace game {
	static auto HandleRunning = reinterpret_cast<void* (*)(void*, void*, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp_method(c_xor("PlayerWalkMovement"), c_xor("HandleRunning"), 3)));
	static auto set_lockstate = reinterpret_cast<void(*)(CursorLockMode)>(*reinterpret_cast<uintptr_t*>(il2cpp_method(c_xor("Cursor"), c_xor("set_lockState"), 1, xorstr("value"), c_xor("UnityEngine"))));
	void init() {
		HandleRunning = reinterpret_cast<void* (*)(void*, void*, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp_method(c_xor("PlayerWalkMovement"), c_xor("HandleRunning"), 3)));
		set_lockstate = reinterpret_cast<void(*)(CursorLockMode)>(*reinterpret_cast<uintptr_t*>(il2cpp_method(c_xor("Cursor"), c_xor("set_lockState"), 1, xorstr("value"), c_xor("UnityEngine"))));
		printf("handlerunning: ", std::to_string((uintptr_t)game::HandleRunning));
	}
}
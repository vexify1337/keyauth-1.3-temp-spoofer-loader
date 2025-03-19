#include "Windows.h"
#include "byte.h"
#include "../ScriptKiddy_Mapper/include/kdmapper.hpp"
NTSTATUS exitCode = 0;
HANDLE iqvw64e_device_handle; //mapper device handle.
struct stupid {
public:

	// im not sure if i did the parameters correctly if not just do them ur self and should map! 
	void spoof() {
		iqvw64e_device_handle = intel_driver::Load();

		if (iqvw64e_device_handle == INVALID_HANDLE_VALUE) {
			exit(1);
		}

		kdmapper::AllocationMode mode = kdmapper::AllocationMode::AllocatePool;

		

		if (!kdmapper::MapDriver(iqvw64e_device_handle, beat_km_bytes, 0, 0, free, true, mode, 0, 0, &exitCode)) {
			exit(100);
		}

		if (!intel_driver::Unload(iqvw64e_device_handle)) {
			Log(L"[-] Warning failed to fully unload vulnerable driver " << std::endl);
		}
	}
}; stupid* BeatUM = new stupid();


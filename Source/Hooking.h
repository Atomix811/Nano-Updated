#pragma once
namespace Protections // protection bools
{
	extern bool g_LogScriptEvents; // just for logg events

	extern bool g_Karma;
	extern bool Anti_CEO_Kick;
	extern bool Anti_CEO_Ban;
}




using Get_Event_Data = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
using IsDlcPresent = bool(std::uint32_t hash);
using GetLabelText = const char* (void* unk, const char* label);

typedef uint32_t* (*__cdecl        fpFileRegister)(int*, const char*, bool, const char*, bool);
typedef void(__cdecl* fpTriggerScriptEvent)(int eventGroup, uint64_t* args, int argCount, int bit);
typedef bool(__cdecl* fpHasModelLoaded)(Hash model);
typedef bool(__cdecl* fpRequestModel)(Hash model);
typedef Vehicle(__cdecl* fpCreateVehicle)(Hash model, Vector3* pos, float heading, BOOL networked, BOOL unk2);
typedef BOOL(__cdecl* fpCreateObject)(Hash model, float x, float y, float z, bool offset, int unk0, int unk1, Object* out, bool isNetworked, bool unk2, bool dynamic);

typedef bool(__cdecl* fpAddOwnedExplosion)(Ped ped, Vector3 pos, int type, float dmgScale, bool isAudible, bool isInvis, float fCamShake);
using fpjoiner = void*;

class Hooking
{
private:
	static BOOL InitializeHooks();
	static void FindPatterns();
	static void FailPatterns(const char* name);

public:
	static std::vector<LPVOID>		m_hooks;
	static uint64_t* m_frameCount;
	static IsDlcPresent* m_is_dlc_present;
	static GetLabelText* m_get_label_text;
	static Get_Event_Data* m_getEvent_Data;

	static PVOID			m_model_spawn_bypass;
	static void* m_native_return;
	static eGameState* m_gamestate;
	static uint64_t			m_world_pointer;
	static __int64** m_global_pointer;
	static fpFileRegister			m_fileregister;

	static eGameState		GetGameState();
	static uint64_t			getWorldPtr();
	static __int64** getGlobalPtr();

	static fpTriggerScriptEvent            trigger_script_event;

	static fpCreateVehicle									create_vehiclee;
	static fpCreateObject									create_objectt;
	static fpHasModelLoaded									has_model_loaded;
	static fpRequestModel							request_model;
	static fpAddOwnedExplosion							add_owned_explosion;
	static void owned_explossion_bypass(bool toggle);

	static void Start(HMODULE hmoduleDLL);
	static void __declspec(noreturn) Cleanup();
	static void onTickInit();
	static bool HookNatives();
	static void defuseEvent(RockstarEvent e, bool toggle);

	// Native function handler type
	typedef void(__cdecl* NativeHandler)(scrNativeCallContext* context);
	struct NativeRegistrationNew
	{
		uint64_t nextRegistration1;
		uint64_t nextRegistration2;
		Hooking::NativeHandler handlers[7];
		uint32_t numEntries1;
		uint32_t numEntries2;
		uint64_t hashes;

		inline NativeRegistrationNew* getNextRegistration()
		{
			uintptr_t result;
			auto v5 = reinterpret_cast<uintptr_t>(&nextRegistration1);
			auto v12 = 2i64;
			auto v13 = v5 ^ nextRegistration2;
			auto v14 = (char*)&result - v5;
			do
			{
				*(DWORD*)&v14[v5] = (DWORD)(v13 ^ *(DWORD*)v5);
				v5 += 4i64;
				--v12;
			} while (v12);

			return reinterpret_cast<NativeRegistrationNew*>(result);
		}

		inline uint32_t getNumEntries()
		{
			return (uint32_t)(((uintptr_t)&numEntries1) ^ numEntries1 ^ numEntries2);
		}

		inline uint64_t getHash(uint32_t index)
		{

			auto naddr = 16 * index + reinterpret_cast<uintptr_t>(&nextRegistration1) + 0x54;
			auto v8 = 2i64;
			uint64_t nResult;
			auto v11 = (char*)&nResult - naddr;
			auto v10 = naddr ^ *(DWORD*)(naddr + 8);
			do
			{
				*(DWORD*)&v11[naddr] = (DWORD)(v10 ^ *(DWORD*)(naddr));
				naddr += 4i64;
				--v8;
			} while (v8);

			return nResult;
		}
	};
	static NativeHandler GetNativeHandler(uint64_t origHash);
};

void WAIT(DWORD ms);

struct Bytes24
{
	BYTE	byte2[24];

	bool	empty();
};

struct twoBytes
{
	BYTE    byte2[2];

	bool    empty();
};

enum eThreadState
{
	ThreadStateIdle = 0x0,
	ThreadStateRunning = 0x1,
	ThreadStateKilled = 0x2,
	ThreadState3 = 0x3,
	ThreadState4 = 0x4,
};

struct scrThreadContext
{
	int ThreadID;
	int ScriptHash;
	eThreadState State;
	int _IP;
	int FrameSP;
	int _SPP;
	float TimerA;
	float TimerB;
	int TimerC;
	int _mUnk1;
	int _mUnk2;
	int _f2C;
	int _f30;
	int _f34;
	int _f38;
	int _f3C;
	int _f40;
	int _f44;
	int _f48;
	int _f4C;
	int _f50;
	int pad1;
	int pad2;
	int pad3;
	int _set1;
	int pad[17];
};

struct scrThread
{
	void* vTable;
	scrThreadContext m_ctx;
	void* m_pStack;
	void* pad;
	void* pad2;
	const char* m_pszExitMessage;
};

struct ScriptThread : scrThread
{
	const char Name[64];
	void* m_pScriptHandler;
	const char gta_pad2[40];
	const char flag1;
	const char m_networkFlag;
	bool bool1;
	bool bool2;
	bool bool3;
	bool bool4;
	bool bool5;
	bool bool6;
	bool bool7;
	bool bool8;
	bool bool9;
	bool bool10;
	bool bool11;
	bool bool12;
	const char gta_pad3[10];
};

/*
//CPatternResult
*/

class CPatternResult
{
public:
	CPatternResult(void* pVoid);
	CPatternResult(void* pVoid, void* pBegin, void* pEnd);
	~CPatternResult();

	template <typename rT>
	rT* get(int offset = 0)
	{
		rT* ret = nullptr;
		if (m_pVoid != nullptr)
			ret = reinterpret_cast<rT*>(reinterpret_cast<char*>(m_pVoid) + offset);
		return ret;
	}

	template <typename rT>
	rT* get_rel(int offset = 0)
	{
		rT* result = nullptr;
		int32_t	rel;
		char* ptr = get<char>(offset);

		if (ptr == nullptr)
			goto LABEL_RETURN;

		rel = *(int32_t*)ptr;
		result = reinterpret_cast<rT*>(ptr + rel + sizeof(rel));

	LABEL_RETURN:
		return result;
	}

	template <typename rT>
	rT* section_begin()
	{
		return reinterpret_cast<rT*>(m_pBegin);
	}

	template <typename rT>
	rT* section_end()
	{
		return reinterpret_cast<rT*>(m_pEnd);
	}

protected:
	void* m_pVoid = nullptr;
	void* m_pBegin = nullptr;
	void* m_pEnd = nullptr;
};

class CMetaData
{
public:
	static uint64_t	begin();
	static uint64_t	end();
	static DWORD	size();
	static void		init();
private:
	static uint64_t	m_begin;
	static uint64_t	m_end;
	static DWORD	m_size;
};

/*
//CPattern
*/

typedef	std::vector<CPatternResult>	vec_result;
class CPattern
{
public:
	CPattern(char* szByte, char* szMask);
	~CPattern();

	CPattern& find(int i = 0, uint64_t startAddress = 0);		//scans for i patterns
	CPattern& virtual_find(int i = 0, uint64_t startAddress = 0);
	CPatternResult	get(int i);				//returns result i

protected:
	char* m_szByte;
	char* m_szMask;
	bool			m_bSet;
	vec_result		m_result;

	bool		match(int i = 0, uint64_t startAddress = 0, bool virt = false);
	bool		byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask);
	uint64_t	find_pattern(uint64_t i64Address, uint64_t end, BYTE* btMask, char* szMask);
	uint64_t	virtual_find_pattern(uint64_t address, BYTE* btMask, char* szMask);
};

struct MinHookKeepalive
{
	MinHookKeepalive();
	~MinHookKeepalive();
};
extern Hooking hooks;
extern MinHookKeepalive g_MinHookKeepalive;
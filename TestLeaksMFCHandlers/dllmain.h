// dllmain.h : Declaration of module class.

class CTestLeaksMFCHandlersModule : public ATL::CAtlDllModuleT<CTestLeaksMFCHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_TestLeaksMFCHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TESTLEAKSMFCHANDLERS, "{9b51aa0f-094a-42c1-a03e-6927ded6997b}")
};

extern class CTestLeaksMFCHandlersModule _AtlModule;

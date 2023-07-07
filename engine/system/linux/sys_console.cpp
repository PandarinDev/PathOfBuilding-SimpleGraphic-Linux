#ifdef __linux__

#include "engine/system/sys_console.h"

class sys_console_linux : public sys_IConsole {

public:

    sys_console_linux(sys_IMain* sysHnd) : sysHnd(sysHnd) {}

    void SetVisible(bool show) override {

    }

	bool IsVisible() override {
        // TODO: Implement
        return false;
    }

	void SetForeground() override {

    }

	void SetTitle(const char* title) override {

    }

private:

    sys_IMain* sysHnd;

};

sys_IConsole* sys_IConsole::GetHandle(sys_IMain* sysHnd)
{
	return new sys_console_linux(sysHnd);
}

void sys_IConsole::FreeHandle(sys_IConsole* hnd)
{
	delete (sys_console_linux*)hnd;
}

#endif
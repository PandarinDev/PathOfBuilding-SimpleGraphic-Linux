#include "engine/system/sys_video.h"
#include "config.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdexcept>

class sys_video_linux : public sys_IVideo {

public:

    sys_video_linux(sys_IMain* sysHnd) : sysHnd(sysHnd), window_handle(nullptr) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW.");
        }
        // TODO: Calculate initial size similar to how the Windows implementation does
        window_handle = glfwCreateWindow(1600, 900, CFG_TITLE, nullptr, nullptr);
        if (!window_handle) {
            throw std::runtime_error("Failed to create GLFW window.");
        }
        glfwMakeContextCurrent(window_handle);
    }

    int Apply(sys_vidSet_s* set) override {
        return 0;
	}

	void SetActive(bool active) override {

	}
		
	void SetForeground() override {

	}
 
	bool IsActive() override {
        return false;
	}
 
	void SizeChanged(int width, int height, bool max) override {

	}
 
	void PosChanged(int x, int y) override {

	}
 
	void GetMinSize(int &width, int &height) override {

	}
 
	void SetVisible(bool vis) override {

	}
		
	bool IsVisible() override {
        return false;
	}
 
	void SetTitle(const char* title) override {
        glfwSetWindowTitle(window_handle, title);
	}

	void* GetWindowHandle() override {
        return window_handle;
	}
			
	void GetRelativeCursor(int &x, int &y) override {
        double x_local, y_local;
        glfwGetCursorPos(window_handle, &x_local, &y_local);
        x = x_local;
        y = y_local;
	}
 
	void SetRelativeCursor(int x, int y) override {
        glfwSetCursorPos(window_handle, x, y);
	}

	bool IsCursorOverWindow() override {
        return false;
	}

private:

    sys_IMain* sysHnd;
    GLFWwindow* window_handle;

};

sys_IVideo* sys_IVideo::GetHandle(sys_IMain* sysHnd)
{
	return new sys_video_linux(sysHnd);
}

void sys_IVideo::FreeHandle(sys_IVideo* hnd)
{
	delete (sys_video_linux*)hnd;
}

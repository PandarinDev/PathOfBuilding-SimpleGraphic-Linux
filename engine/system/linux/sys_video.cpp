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
		// TODO: Apply properties from the received set
        return 0;
	}

	void SetActive(bool active) override {
		// TODO: Probably not relevant on Linux, but double check
	}
		
	void SetForeground() override {
		glfwFocusWindow(window_handle);
	}
 
	bool IsActive() override {
		// TODO: It's probably alright to always return true here, but double check
        return true;
	}
 
	void SizeChanged(int width, int height, bool max) override {
		glfwSetWindowSize(window_handle, width, height);
		if (max) {
			glfwMaximizeWindow(window_handle);
		}
	}
 
	void PosChanged(int x, int y) override {
		glfwSetWindowPos(window_handle, x, y);
	}
 
	void GetMinSize(int& width, int& height) override {
		// TODO: This should probably be properly calculated instead
		width = 200;
		height = 200;
	}
 
	void SetVisible(bool vis) override {
		glfwSetWindowAttrib(window_handle, GLFW_VISIBLE, vis ? GLFW_TRUE : GLFW_FALSE);
	}
		
	bool IsVisible() override {
        return glfwGetWindowAttrib(window_handle, GLFW_VISIBLE);
	}
 
	void SetTitle(const char* title) override {
        glfwSetWindowTitle(window_handle, title);
	}

	void* GetWindowHandle() override {
        return window_handle;
	}
			
	void GetRelativeCursor(int& x, int& y) override {
        double x_local, y_local;
        glfwGetCursorPos(window_handle, &x_local, &y_local);
        x = x_local;
        y = y_local;
	}
 
	void SetRelativeCursor(int x, int y) override {
        glfwSetCursorPos(window_handle, x, y);
	}

	bool IsCursorOverWindow() override {
		return glfwGetWindowAttrib(window_handle, GLFW_HOVERED);
	}

private:

    sys_IMain* sysHnd;
    GLFWwindow* window_handle;

};

sys_IVideo* sys_IVideo::GetHandle(sys_IMain* sysHnd) {
	return new sys_video_linux(sysHnd);
}

void sys_IVideo::FreeHandle(sys_IVideo* hnd) {
	delete (sys_video_linux*)hnd;
}

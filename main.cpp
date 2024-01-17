#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <cstring>

// Constants
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
	// Public Methods
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}
private:
	// Private Data Members
	GLFWwindow* window;
	VkInstance instance;

	// Private Methods
	void initWindow() {
		std::cout << "Initializing GLFW...";
		if (glfwInit()) {
			std::cout << "GLFW Initialized.\n";
		} else {
			std::runtime_error("GLFW Failed to Initialize!");
		}
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		std::cout << "Creating GLFW window...";
		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		if (window == nullptr) {
			std::runtime_error("Failed to create GLFW window!");
		} else {
			std::cout << "GLFW window created.\n";
		}
	}

	void initVulkan() {
		// Creating Instance
		
		// Creating AppInfo Struct
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;
		
		// Getting required GLFW extensions
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		// Getting available Vulkan Instance Extensions
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		// Logging Extensions
		std::cout << "\nAvailable Vulkan Extensions:\n";
		for (const auto& extension : extensions) {
			std::cout << "\t" << extension.extensionName << "\n";
		}

		// Logging required GLFW extensions
		uint32_t supportedExtensions = 0;
		std::cout << "\nRequired GLFW Extensions\n";
		for (int i = 0; i < glfwExtensionCount; i++) {
			std::cout << "\t" << glfwExtensions[i] << "\t";

			// Logs "EXISTS" next to extension if it exists
			for (const auto& extension : extensions) {
				if (strcmp(extension.extensionName, glfwExtensions[i]) == 0) {
					std::cout << "(Available)";
					supportedExtensions++;
					break;
				}
			}
			std::cout << "\n";
		}

		if (supportedExtensions < glfwExtensionCount) {
			std::runtime_error("Required extensions not available!");
		} else {
			std::cout << "\nAll required extensions are available -- All Good.\n";
		}

		// Creating Instance Info Struct
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		// Initializing Vulkan Instance & Validating
		if (vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS) {
			std::cout << "\nVulkan Instance created.\n";
		} else {
			throw std::runtime_error("Failed to create instance!");
		}
	}

	void mainLoop() {
		std::cout << "\nEntering mainLoop()\n";
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void cleanup() {
		// Destroying Vulkan
		vkDestroyInstance(instance, nullptr);

		// Destroying GLFW
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

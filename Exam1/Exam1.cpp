#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class FileManager {
public:
    void showDriveContents() {
        std::cout << "Drive Contents:" << std::endl;
        for (auto& entry : fs::directory_iterator(fs::current_path())) {
            std::cout << entry.path().filename() << std::endl;
        }
    }

    bool createFolder(const std::string& folderName) {
        try {
            fs::create_directory(folderName);
            return true;
        }
        catch (const fs::filesystem_error& ex) {
            std::cerr << "Error creating folder: " << ex.what() << std::endl;
            return false;
        }
    }

    bool removeEntry(const std::string& path) {
        try {
            fs::remove_all(path);
            return true;
        }
        catch (const fs::filesystem_error& ex) {
            std::cerr << "Error removing entry: " << ex.what() << std::endl;
            return false;
        }
    }

    bool renameEntry(const std::string& oldName, const std::string& newName) {
        try {
            fs::rename(oldName, newName);
            return true;
        }
        catch (const fs::filesystem_error& ex) {
            std::cerr << "Error renaming entry: " << ex.what() << std::endl;
            return false;
        }
    }

    uintmax_t calculateSize(const std::string& path) {
        try {
            return fs::file_size(path);
        }
        catch (const fs::filesystem_error& ex) {
            std::cerr << "Error calculating size: " << ex.what() << std::endl;
            return 0;
        }
    }

    // Виконує пошук по масці у заданій директорії
    std::vector<std::string> search(const std::string& directory, const std::string& mask) {
        std::vector<std::string> results;
        try {
            for (auto& entry : fs::recursive_directory_iterator(directory)) {
                if (entry.path().filename().string().find(mask) != std::string::npos) {
                    results.push_back(entry.path().string());
                }
            }
        }
        catch (const fs::filesystem_error& ex) {
            std::cerr << "Error searching: " << ex.what() << std::endl;
        }
        return results;
    }
};

int main() {
    FileManager fileManager;

    fileManager.showDriveContents();

    fileManager.createFolder("TestFolder");

    fileManager.removeEntry("TestFolder");

    fileManager.createFolder("TestFolder");
    fileManager.renameEntry("TestFolder", "NewFolder");

    std::cout << "Size of NewFolder: " << fileManager.calculateSize("NewFolder") << " bytes" << std::endl;

    std::vector<std::string> searchResults = fileManager.search(".", ".txt");
    std::cout << "Files with .txt extension:" << std::endl;
    for (const auto& result : searchResults) {
        std::cout << result << std::endl;
    }

    return 0;
}

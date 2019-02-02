#include "Commands.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>  /* defines FILENAME_MAX */
#include <ctime>
#include <filesystem>
namespace fs = std::filesystem;

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#define chdir _chdir
#define stat _stat
#else
#include <unistd.h>
#endif
#define REQUIRED_ARGS(x) if(args.size() < x) { printf("Incorrect number of arguments (%d required)\n", x); return; }

namespace chank
{
    void exit(Tree* tree, std::vector<std::string> &args) { }

    void pwd(Tree* tree, std::vector<std::string> &args)
    {
        printf("%s\n", tree->GetCurrentPath().c_str());
    }

    void cd(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(1);
        tree->ChangeCurrent(args.front().c_str());
    }

    void ls(Tree* tree, std::vector<std::string> &args)
    {
        for (auto& child : tree->GetCurrent()->GetChilds())
        {
            printf("%s\t", child->IsDir() ? "DIR" : "FILE");
            printf("%s\t", child->GetName());
            printf("%ld\t", child->GetSize());

            auto modificationDate = child->GetLastModification();
            printf("%s", asctime(gmtime(&modificationDate)));
        }
    }

    void upload(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(1);
        char cwd[FILENAME_MAX];
        getcwd(cwd, sizeof(cwd));
        for (const auto &entry : fs::directory_iterator(cwd))
        {
            auto name = entry.path().filename().string();
            if (name != args.front()) continue;

            // TODO!!!
            if (entry.is_directory()) break;
            tree->CreateNode(name.c_str(), false);
        }

        tree->Save(); // TODO check this.. idk if it should be always called
    }

    void mkdir(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(1);
        tree->CreateNode(args.front().c_str(), true);
    }

    void rmdir(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(1);
        if (auto node = tree->GetCurrent()->FindChild(args.front().c_str()); node != nullptr)
        {
            if (!node->IsDir())
            {
                printf("-bash: rmdir: %s: Not a directory. Use `rm` instead.\n", args.front().c_str());
                return;
            }

            if (node->GetChilds().size() > 0)
            {
                printf("-bash: rmdir: %s: Not empty.\n", args.front().c_str());
                return;
            }
            tree->GetCurrent()->RemoveChild(node->GetId());
            tree->DecrementLength();
            tree->Save();
        }
    }

    void rm(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(1);
        if (auto node = tree->GetCurrent()->FindChild(args.front().c_str()); node != nullptr)
        {
            if (node->IsDir())
            {
                printf("-bash: rm: %s: Is a directory. Use `rmdir` instead.\n", args.front().c_str());
                return;
            }

            tree->GetCurrent()->RemoveChild(node->GetId());
            tree->DecrementLength();
            tree->Save();
        }
    }

    void touch(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(1);
        tree->CreateNode(args.front().c_str(), false);
    }

    void mv(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(2);
        if (auto node = tree->GetCurrent()->FindChild(args.front().c_str()); node != nullptr)
        {
            node->UpdateNode(args.back().c_str());
            tree->Save();
        }
    }

    void cp(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(2);
        if (auto node = tree->GetCurrent()->FindChild(args.front().c_str()); node != nullptr)
        {
            // copying destination -> inside existent directory
            auto destination = args.back();
            if (destination.find('/'))
            {
                auto dirName = destination.substr(0, destination.find('/'));
                auto dir = tree->GetCurrent()->FindChild(dirName.c_str());
                if (dir != nullptr)
                {
                    // If the directory exists
                    auto oldCurrent = tree->GetCurrent()->GetName();
                    tree->ChangeCurrent(dir->GetName());
                    tree->CopyNode(*node);
                    tree->ChangeCurrent(oldCurrent);
                }
                else
                {
                    //TODO: dir doesn't exist | create?
                    int b = 1;
                }
            }

            tree->Save();
        }
    }

    void lpwd(Tree* tree, std::vector<std::string> &args)
    {
        char cwd[FILENAME_MAX];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }

    void lcd(Tree* tree, std::vector<std::string> &args)
    {
        REQUIRED_ARGS(1);
        if (chdir(args.front().c_str()) == -1)
        {
            printf("-bash: lcd: %s: Not a directory\n", args.front().c_str());
            return;
        }
    }

    void lls(Tree* tree, std::vector<std::string> &args)
    {
        // TODO: fix the format | file names have different sizes
        char cwd[FILENAME_MAX];
        getcwd(cwd, sizeof(cwd));
        for (const auto &entry : fs::directory_iterator(cwd))
        {
            printf("%s\t", entry.is_directory() ? "DIR" : "FILE");
            printf("%s\t", entry.path().filename().string().c_str());
            auto size = entry.is_directory() ? 4096 : static_cast<long>(entry.file_size());
            printf("%ld\t", size);

            struct stat result;
            if (stat(entry.path().string().c_str(), &result) == 0)
                printf("%s", asctime(gmtime(&result.st_mtime)));
        }
    }
}
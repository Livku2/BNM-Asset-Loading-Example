#include "AssetLoading.h"

using namespace BNM;

void *AssetLoading::LoadBundle(std::string directory) {;
    Method<void*> LoadFromFile = Class("UnityEngine", "AssetBundle").GetMethod("LoadFromFile", 1);
    return LoadFromFile(CreateMonoString(directory));
}

void *AssetLoading::InstantiateAsset(void *bundle, string name) {
    Method<void*> LoadAsset = Class("UnityEngine", "AssetBundle").GetMethod("LoadAsset", 2);
    auto prefab = LoadAsset(CreateMonoString(name), Class("UnityEngine", "GameObject").GetMonoType());
    auto Unload = reinterpret_cast<void (*)(void *, bool)>(GetExternMethod("UnityEngine.AssetBundle::Unload"));
    Unload(bundle, false);
    return prefab;
}

void *AssetLoading::InstantiateAssetFromDir(string directory, string name) {
    return InstantiateAsset(LoadBundle(directory), name);
}

void *AssetLoading::LoadBundleFromDownloadLink(string link, string directory, string name) {
    auto UnityWebRequestClass = Class("UnityEngine.Networking", "UnityWebRequest");
    auto DownloadHandlerClass = Class("UnityEngine.Networking", "DownloadHandler");
    Method<bool> get_isDone = DownloadHandlerClass.GetMethod("get_isDone");
    Method<void> set_downloadHandler = UnityWebRequestClass.GetMethod("set_downloadHandler");
    Method<void*> get_downloadHandler = UnityWebRequestClass.GetMethod("get_downloadHandler");
    auto DirectoryClass = Class("System.IO", "Directory");
    Method<void*> CreateDirectory = DirectoryClass.GetMethod("CreateDirectory");
    Method<bool> DirectoryExists = DirectoryClass.GetMethod("Exists");
    auto FileClass = Class("System.IO", "File");
    Method<bool> FileExists = FileClass.GetMethod("Exists");
    Method<Structures::Mono::String*> Combine = Class("System.IO", "Path").GetMethod("Combine", 2);

    auto fileDirectory = Combine(CreateMonoString(directory), CreateMonoString(name));

    if(DirectoryExists(CreateMonoString(directory))){
        if(FileExists(CreateMonoString(name))){
            LoadBundle(fileDirectory->str());
        }
    }
    else{
        CreateDirectory(CreateMonoString(directory));
    }

    auto UnityWebRequest = UnityWebRequestClass.CreateNewObjectParameters(CreateMonoString(link));
    set_downloadHandler[UnityWebRequest](DownloadHandlerClass.CreateNewObjectParameters(fileDirectory));

    while (!get_isDone(get_downloadHandler[UnityWebRequest]())){
        sleep(1);
    }

    return LoadBundle(fileDirectory->str());
}
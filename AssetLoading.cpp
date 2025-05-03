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

void *AssetLoading::InstantiateAssetFromDir(std::string directory, std::string name) {
    return InstantiateAsset(LoadBundle(directory), name);
}
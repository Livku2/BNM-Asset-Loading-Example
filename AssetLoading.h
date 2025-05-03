#include "PUT YOUR BNM HEADERS HERE"

using namespace std;

namespace AssetLoading{
    void * LoadBundle(string directory);
    void * InstantiateAssetFromDir(string directory, string name);
    void * InstantiateAsset(void* bundle, string name);
}
#include "PUT YOUR BNM HEADERS HERE"
#include "unistd.h"

using namespace std;

namespace AssetLoading{
    void * LoadBundle(string directory);
    void * InstantiateAssetFromDir(string directory, string name);
    void * InstantiateAsset(void* bundle, string name);
    void * LoadBundleFromDownloadLink(string link, string storageDir, string fileName);
}
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <set>

using std::shared_ptr;
using std::vector;
using std::string;
using std::wstring;
using std::function;
using std::unordered_map;
using std::set;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>

#include <ITPMememory.h>
#include <singleton.h>
#include <StringUtils.h>
#include <dbg_assert.h>
#include <itpmath.h>
#include <Timing.h>
#include <poolalloc.h>

#include <DelegateList.h>
#include <InputManager.h>

#include <GraphicsDriver.h>

#include <Camera.h>

#include <Mesh.h>
#include <AnimComponent.h>
#include <MeshComponent.h>
#include <SceneGraph.h>

#include <GameObject.h>
#include <LightingConstants.h>
#include <GameWorld.h>
#include <GameClassRegistry.h>

#include <App.h>
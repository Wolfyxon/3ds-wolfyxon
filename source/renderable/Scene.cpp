#include "../../include/renderable/Scene.h"
#include "../../include/renderable/Sprite.h"

Scene::Scene(gfxScreen_t screen, u32 backgroundColor_){
    name = "Scene";
    renderTarget = C2D_CreateScreenTarget(screen, GFX_LEFT);
    backgroundColor = backgroundColor_;
}


string* getExtended(){
    string* ext = new string[4];
    ext[0] = "Debuggable";
    ext[1] = "Classified";
    ext[2] = "TreeElement";
    ext[3] = "Renderable";
    return ext;
}

void Scene::render(){
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(renderTarget, backgroundColor);
    C2D_SceneBegin(renderTarget);

    vector<TreeElement *> descendants = getDescendants();
    for(TreeElement *desc : descendants){
        if (is_base_of<Renderable* , decltype(desc)>::value){
            Renderable *rend = (Renderable*)desc;
            rend->render();
        }
    }
    //descendants.clear();
    C3D_FrameEnd(0);
}

#include "../include/TreeElement.h"

TreeElement::TreeElement(string name_){
    name = name_;
}

TreeElement::~TreeElement(){
    free();
}

vector<TreeElement*> TreeElement::getChildren(){
    return children;
}

vector<TreeElement*> TreeElement::getDescendants(){
    vector<TreeElement*> res;
    for(size_t i=0; i<children.size(); i++){
        TreeElement* child = children[i];
        res.push_back(child);
        vector<TreeElement*> sub = child->getDescendants();
        for(size_t ii=0; i<sub.size(); ii++){
            res.push_back(sub[i]);
        }
    }
    return res;
}

vector<TreeElement*> TreeElement::getAncestors(){
    vector<TreeElement*> res;
    TreeElement* current = this;
    while (current->parent != NULL){
        current = current->parent;
        res.push_back(current);
    }
    return res;
}

void TreeElement::addChild(TreeElement* child){
    if(child->parent == this) return;

    child->parent = this;
    children.push_back(child);
}

void TreeElement::removeChild(TreeElement* child, bool free){
    if(!hasChild(child)) return;
    int idx = getChildIdx(child);
    if(idx == -1) return;
    vector<TreeElement*>::iterator it = children.begin();
    std::advance(it, idx);
    children.erase(it);
    child->setParent(NULL);
    if(free) child->free();
}

int TreeElement::getChildIdx(TreeElement* child){
    for(int i=0; i<(int)children.size(); i++){
        if(children[i] == child) return i;
    }
    return -1;
}

void TreeElement::free(){
    if(parent != NULL) parent->removeChild(this,false);
    for(size_t i=0; i<children.size(); i++){
        TreeElement* ch = children[i];
        ch->free();
        delete ch;
    }
    children.clear();
}

bool TreeElement::hasChild(TreeElement* child){
    return (
        child->parent == this && 
        (std::find(children.begin(), children.end(), child) != children.end()) 
    );
}

TreeElement* TreeElement::getChildByName(string name_){
    for(size_t i=0;i<children.size();i++){
        TreeElement* ch = children[i];
        if(ch->name.compare(name_)) return ch;
    }
    return NULL;
}

TreeElement* TreeElement::getNthChild(size_t index){
    if(children.size()-1 < index ) return NULL;
    return children[index];
}

TreeElement* TreeElement::getParent(){
    return parent;
}

void TreeElement::setParent(TreeElement* newParent){
    if(parent == newParent) return;
    if(parent != NULL) parent->removeChild(this,false);
    if(newParent != NULL){
        newParent->addChild(this);
    }
    parent = newParent;
    
}
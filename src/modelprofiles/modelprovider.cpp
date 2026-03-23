#include "modelprovider.hh"
#include "R18ModelProfile.hh"

ModelProvider::ModelProvider()
{
    modelProfile = new R18ModelProfile();
    this->LoadModel();
}
void ModelProvider::LoadModel() 
{
    this->Groups = modelProfile->LoadModel();
  //TODO:check if local exist or fall back to default

}
std::vector<GroupBlock*> ModelProvider::GetGroups()
{
    return this->Groups;
}

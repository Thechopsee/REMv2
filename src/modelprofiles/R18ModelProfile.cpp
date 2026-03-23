#include "R18ModelProfile.hh"
#include "../actions/LinearBlinkAction.cpp"
#include "../actions/BlinkAction.cpp"
#include "../actions/RandomBlinkAction.cpp"
#include "../objects/ControllBlocks/ActionBlock.hh"
#include "../objects/ControllBlocks/OnOffBlock.hh"
#include "../objects/ControllBlocks/SliderBlock.hh"
#include "../objects/ControllBlocks/InputSliderBlock.hh"

std::vector<GroupBlock*> R18ModelProfile::LoadModel() 
{
  std::vector<GroupBlock*> Groups;
  const std::vector<int> rightBlockPins = {12,14,26,27};
  const std::vector<int> leftBlockPins = {22,23,19,21};
   const std::vector<int> allBlockPins = {12,14,26,27,22,23,19,21};


  Groups.push_back(new GroupBlock(0,controll));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 0, {32,33},"Front Left"));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 1, {2,15},"Front Right"));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 0, {0,4},"Back"));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 0, {0,4,2,15,32,33},"All"));
  Groups.push_back(new GroupBlock(1,controll));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 0, leftBlockPins,"Left Block"));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 0, rightBlockPins,"Right Block"));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 0, allBlockPins,"All Blocks"));
  Groups.push_back(new GroupBlock(2,action));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, rightBlockPins,"Action Right", new LinearBlinkAction()));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, leftBlockPins,"Action Left", new LinearBlinkAction()));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, allBlockPins,"Action All", new LinearBlinkAction()));
  Groups.push_back(new GroupBlock(3,action));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, rightBlockPins,"Action Blink Right", new BlinkAction()));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, leftBlockPins,"Action Blink Left", new BlinkAction()));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, allBlockPins,"Action Blink All", new BlinkAction()));
  Groups.push_back(new GroupBlock(4,action));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, rightBlockPins,"Action Random Right", new RandomBlinkAction()));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, leftBlockPins,"Action Random Left", new RandomBlinkAction()));
  Groups.back()->blocks.push_back(new ActionBlock(3, 0, allBlockPins,"Action Random All", new RandomBlinkAction()));
  //TODO: bug sliders stop work for all other controll blocks
  Groups.push_back(new GroupBlock(5,slider));
  Groups.back()->blocks.push_back(new SliderBlock(5,0,{0,4,2,15,32,33},"Slider Red All"));
  Groups.back()->blocks.push_back(new SliderBlock(5,0,allBlockPins,"Slider Lights All"));
  Groups.push_back(new GroupBlock(6,inputSlider));
  Groups.back()->blocks.push_back(new InputSliderBlock(6,0,{0,4,2,15,32,33},"Input Slider Red All"));
  Groups.back()->blocks.push_back(new InputSliderBlock(6,0,allBlockPins,"Input Slider Lights All"));



  return Groups;
}

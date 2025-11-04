class ActionBlock: public BasicBlock
{
  private:
     bool isActive;
     Action* action
  public:
    ActionBlock(int id, int blok_id, const std::vector<int>& pins, const char* name);
    void setPin(bool dat);
    void resolveInput(String request);
    void update();
};
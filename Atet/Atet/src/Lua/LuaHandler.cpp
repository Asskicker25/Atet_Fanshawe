#include "LuaHandler.h"

#include"LuaManager.h"
LuaHandler::LuaHandler()
{



}

LuaHandler::LuaHandler(const std::string& luaScript)
{
    L = luaL_newstate();
    luaL_openlibs(L);

    SetScript(luaScript);

 
}

LuaHandler::~LuaHandler()
{
	lua_close(L);
}

void LuaHandler::SetScript(const std::string& LuaScript)
{
    this->Script = LuaScript;
}

void LuaHandler::RegisterFunctionInScript() 
{
    LuaManager::GetInstance().RegisterCommands(L);
}

void LuaHandler::ExecuteScirpt(Model*& model)
{
    LuaManager::GetInstance().ExecuteStateWithFile(L, Script, model);
}

void LuaHandler::ExecuteScirpt()
{
    LuaManager::GetInstance().ExecuteStateWithFile(L, Script);
}

lua_State* LuaHandler::GetLuaState() const
{
    return L;
}

std::string LuaHandler::GetScript() const
{
    return Script;
}


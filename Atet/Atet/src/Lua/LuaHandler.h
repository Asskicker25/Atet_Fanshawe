#pragma once
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <lua/lua.hpp>
#include <iostream>
#include <Graphics/Mesh/Model.h>


class LuaHandler
{
public:
	LuaHandler();
	LuaHandler(const std::string& luaScript);
	~LuaHandler();

	void SetScript(const std::string& LuaScript);
	void RegisterFunctionInScript();
	void ExecuteScirpt(Model*& model);
	void ExecuteScirpt();

	lua_State* GetLuaState() const;

	std::string GetScript() const;
private:
	lua_State* L;
	std::unordered_map<std::string, std::function<void(lua_State*)>> commandRegistry;

	std::string Script;


};


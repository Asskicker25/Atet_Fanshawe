#pragma once
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <map>
#include <lua/lua.hpp>
#include <iostream>
#include "Command/CommandManager.h"
#include <Graphics/Mesh/Model.h>
//#include "GraphicsRender.h" its made into instance
#include <Physics/PhysicsEngine.h>
//#include "EasingTechiques.h" not needed for now 

class MoveTo;
class OrientTo;
class FollowObject;
class WaitForSeconds;
class GameObject;
class MoveAlongAxisWithTime;
class ScaleTo;
class RotateAlongAxisWithTime;
class FollowCurveWithTime;
class SphereTest;
class LookAt;
class Ball;
class Barrel;
class SoundCommand;

class LuaManager
{
public:

	~LuaManager();

	static LuaManager& GetInstance();

	void RegisterCommands(lua_State* L);
	void ExecuteStateWithFile(lua_State* L, const std::string& scriptName, Model*& model);
	void ExecuteStateWithFile(lua_State* L, const std::string& scriptName);

	void SetModel(Model*& model);
	void SetModelList(const std::vector<Model*>& modelList);
	void SetGameObjectList(const std::vector<GameObject*>& GameobjectList);


	

	void FindModelBasedOnName(const std::string& name);
	void FindGameObjectBasedOnName(const std::string& name);
	void AddModelsInMap(Model* model);
	void AddGameObjectInMap(GameObject* model, const std::string& tag);

	bool CheckLua(lua_State* L, int r);

	Model* FindModel(const std::string& name);
	GameObject* FindGameObject(const std::string& name);
	Model* GetModel();



	 std::map<std::string, Model*> modelMap;

	 std::map<std::string, GameObject* > gameObjectMap;
private:

	LuaManager();
	


	static int LuaBeginCommand(lua_State* L);
	static int LuaEndCommand(lua_State* L);

	static int LuaMoveToWrapper(lua_State* L);
	static int LuaOrientToWrapper(lua_State* L);
	static int LuaScaleToWrapper(lua_State* L);

	static int LuaSetGameObject(lua_State* L);

	static int LuaFollowObject(lua_State* L);

	static int LuaSpawnGameObject(lua_State* L);

	static  int LuaWaitForSeconds(lua_State* L);
	static  int LuaMoveAlongAxis(lua_State* L);
	static  int LuaRotateAlongAxis(lua_State* L);

	static  int LuaFollowWithTime(lua_State* L);
	static  int LuaAddPoint(lua_State* L);

	static  int LuaSetLookAtOffset(lua_State* L);
	static  int LuaSetLookAtBool(lua_State* L);

	static  int LuatLookAt(lua_State* L);

	static  int LuaSetCollisionTrigger(lua_State* L);

	static int LuaPlaySound(lua_State* L);


	Model* model;
	GameObject* gameObject;

	//GraphicsRender* renderer;
	Shader* shader;
	PhysicsEngine* engine;

};


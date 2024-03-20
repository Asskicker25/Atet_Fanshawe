#include "LuaManager.h"
#include "MoveTo.h"
#include "OrientTo.h"
#include "FollowObject.h"
#include "WaitForSeconds.h"
#include "MoveAlongOneAxisWithTime.h"
#include "GameObject.h"
#include "ScaleTo.h"
#include "Sphere.h"	
#include "RotateAlongAxisWithTime.h"
#include "FollowCurveWithTime.h"
#include "LookAt.h"
#include "Ball.h"
#include "SpawnObject.h"
#include "../Barrel/Barrel.h"
#include "Command/SoundCommand.h"

LuaManager::LuaManager()
{
}

LuaManager::~LuaManager()
{
}

LuaManager& LuaManager::GetInstance()
{
	static LuaManager instance;
	return instance;
}

void LuaManager::RegisterCommands(lua_State* L)
{
	lua_register(L, "SetGameObject", LuaSetGameObject);
	lua_register(L, "BeginCommand", LuaBeginCommand);
	lua_register(L, "MoveTo", LuaMoveToWrapper);
	lua_register(L, "OrientTo", LuaOrientToWrapper);
	lua_register(L, "ScaleTo", LuaScaleToWrapper);
	lua_register(L, "Endcommand", LuaEndCommand);
	lua_register(L, "FollowObject", LuaFollowObject);
	lua_register(L, "SpawnObject", LuaSpawnGameObject);
	lua_register(L, "WaitForSeconds", LuaWaitForSeconds);
	lua_register(L, "MoveAlongAxisWithTime", LuaMoveAlongAxis);
	lua_register(L, "RotateAlongAxisWithTime", LuaRotateAlongAxis);
	lua_register(L, "FollowWithTime", LuaFollowWithTime);
	lua_register(L, "AddPoint", LuaAddPoint);
	lua_register(L, "SetLookAtOffset", LuaSetLookAtOffset);
	lua_register(L, "SetLookAtBool", LuaSetLookAtBool);
	lua_register(L, "LookAt", LuatLookAt);
	lua_register(L, "SetCollisionTrigger", LuaSetCollisionTrigger);

}

void LuaManager::ExecuteStateWithFile(lua_State* L, const std::string& scriptName, Model*& modelref)
{
	    SetModel(modelref);

		if (!GetModel())
		{
			std::cout << "Model is null for script : " << scriptName << std::endl;
		}
		else
		{
			if (CheckLua(L, luaL_dofile(L, scriptName.c_str())))
			{

			}
		}

		model = nullptr;
}

void LuaManager::ExecuteStateWithFile(lua_State* L, const std::string& scriptName)
{
	if (CheckLua(L, luaL_dofile(L, scriptName.c_str())))
	{

	}
	//	model = nullptr;
}

void LuaManager::SetModel( Model*& model)
{
	this->model = model;
	
}

void LuaManager::SetModelList(const std::vector<Model*>& modelList)
{
	for (Model* model : modelList)
	{
		modelMap[model->id] = model;
	}
}

void LuaManager::SetGameObjectList(const std::vector<GameObject*>& GameobjectList)
{
	for (GameObject* gameObject : GameobjectList)
	{
		gameObjectMap[gameObject->id] = gameObject;
	}
}





void LuaManager::FindModelBasedOnName(const std::string& name)
{
	if (!name.empty())
	{
		model = modelMap[name];
	}
	else
	{
		std::cout << " Cannot find Model with name " << name << std::endl;
	}
}

void LuaManager::FindGameObjectBasedOnName(const std::string& name)
{
	if (!name.empty())
	{
		gameObject = gameObjectMap[name];
	}
	else
	{
		std::cout << " Cannot find game object with name " << name << std::endl;
	}
}

void LuaManager::AddModelsInMap(Model* model)
{
	if (model!=nullptr)
	{
		modelMap[model->id] = model;
	}
}
                           
void LuaManager::AddGameObjectInMap(GameObject* gameObject , const std::string& tag)
{
	if (gameObject != nullptr)
	{
		gameObjectMap[tag] = gameObject;
	}
}

Model* LuaManager::FindModel(const std::string& name)
{
	if (!name.empty())
	{
		return modelMap[name];
	}
	else
	{
		std::cout << "Model is null (LUA MANAGER)" << std::endl;
		return nullptr;
	}
	
}

GameObject* LuaManager::FindGameObject(const std::string& name)
{
	if (!name.empty())
	{
		return  gameObjectMap[name];
	}

	std::cout << "GAMEOBJECT is null (LUA MANAGER)" << std::endl;
	return nullptr;
}

bool LuaManager::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

 Model* LuaManager::GetModel()
{
	
	return model;
}







int LuaManager::LuaBeginCommand(lua_State* L)
{
	int paramLength = lua_gettop(L);

	if (paramLength == 2)
	{
		std::string groupTypeStr = lua_tostring(L, 1); // Serial or Parallel
		int goupdId = lua_tonumber(L, 2); // Group ID
		int groupType = 0;


		if (groupTypeStr == "SERIAL")
		{
			groupType = 0;
		}
		else if (groupTypeStr == "PARALLEL")
		{
			groupType = 1;
		}
		std::cout << "BeginCommandGroup id: " << goupdId << std::endl;
		std::cout << "BeginCommandGroup Type: " << groupTypeStr << std::endl;

		CommandManager::GetInstance().BeginCommandGroup((CommandGroupType)groupType, goupdId);
	}
	else if(paramLength == 1)
	{
		int goupdId = lua_tonumber(L, 1); // Group ID

		std::cout << "BeginCommandGroup id: " << goupdId << std::endl;
		std::cout << "BeginCommandGroup Type: " << "SERIAL" << std::endl;

		CommandManager::GetInstance().BeginCommandGroup(SERIES, goupdId);
	}

	return 0;
}

int LuaManager::LuaEndCommand(lua_State* L)
{
	int paramLength = lua_gettop(L);
	int goupdId = lua_tonumber(L, 1);

	std::cout << "EndCommandGroup id: " << goupdId << std::endl;
	CommandManager::GetInstance().EndCommandGroup(goupdId);

	return 0;
}


int LuaManager::LuaMoveToWrapper(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float x = static_cast<float>(lua_tonumber(L, 1));
	float y = static_cast<float>(lua_tonumber(L, 2));
	float z = static_cast<float>(lua_tonumber(L, 3));

	glm::vec3 target(x, y, z);

	float time = static_cast<float>(lua_tonumber(L, 4));
	float easeInTime;
	float easeOutTime;

	EaseType easeInType = EaseType::NONE;
	EaseType easeOutType = EaseType::NONE;

	Command* command = nullptr;

	switch (paramLength)
	{
	case 4:
		command = new MoveTo(GetInstance().gameObject, target, time);
		break;
	case 5:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		command = new MoveTo(GetInstance().gameObject, target, time, easeInTime);
		break;
	case 6:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		easeOutTime = static_cast<float>(lua_tonumber(L, 6));
		command = new MoveTo(GetInstance().gameObject, target, time, easeInTime, easeOutTime);
		break;

	case 7:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		easeOutTime = static_cast<float>(lua_tonumber(L, 6));

		easeInType = GetEaseTypeWithName(lua_tostring(L, 7));

		command = new MoveTo(GetInstance().gameObject, target, time, easeInTime, easeOutTime, easeInType,easeOutType);
		break;

	case 8:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		easeOutTime = static_cast<float>(lua_tonumber(L, 6));

		easeInType = GetEaseTypeWithName(lua_tostring(L, 7));
		easeOutType = GetEaseTypeWithName(lua_tostring(L, 8));

		command = new MoveTo(GetInstance().gameObject, target, time, easeInTime, easeOutTime, easeInType, easeOutType);
		break;

	}

	CommandManager::GetInstance().AddCommands(command);  

	return 0;
}

int LuaManager::LuaOrientToWrapper(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float x = static_cast<float>(lua_tonumber(L, 1));
	float y = static_cast<float>(lua_tonumber(L, 2));
	float z = static_cast<float>(lua_tonumber(L, 3));

	glm::vec3 targetRotation(x, y, z);

	float time = static_cast<float>(lua_tonumber(L, 4));
	float easeInTime;
	float easeOutTime;
	
	EaseType easeInType = EaseType::NONE;
	EaseType easeOutType = EaseType::NONE;

	Command* command = nullptr;

	switch (paramLength)
	{
	case 4:
		command = new OrientTo(GetInstance().gameObject, targetRotation, time);
		break;
	case 5:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		command = new OrientTo(GetInstance().gameObject, targetRotation, time, easeInTime);
		break;
	case 6:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		easeOutTime = static_cast<float>(lua_tonumber(L, 6));
		command = new OrientTo(GetInstance().gameObject, targetRotation, time, easeInTime, easeOutTime);
		break;

	case 7:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		easeOutTime = static_cast<float>(lua_tonumber(L, 6));

		 easeInType = GetEaseTypeWithName(lua_tostring(L, 7));
	
		 command = new OrientTo(GetInstance().gameObject, targetRotation, time, easeInTime, easeOutTime, easeInType);
		break;

	case 8:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		easeOutTime = static_cast<float>(lua_tonumber(L, 6));

		easeInType = GetEaseTypeWithName(lua_tostring(L, 7));
		easeOutType = GetEaseTypeWithName(lua_tostring(L, 8));

		command = new OrientTo(GetInstance().gameObject, targetRotation, time, easeInTime, easeOutTime, easeInType, easeOutType);
		break;

	}

	CommandManager::GetInstance().AddCommands(command);
	return 0;
}

int LuaManager::LuaScaleToWrapper(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float x = static_cast<float>(lua_tonumber(L, 1));
	float y = static_cast<float>(lua_tonumber(L, 2));
	float z = static_cast<float>(lua_tonumber(L, 3));

	glm::vec3 targetScale(x, y, z);

	float time = static_cast<float>(lua_tonumber(L, 4));


	//Model* model = GetInstance().model;

	GameObject* gameObject = GetInstance().gameObject;

	Command* command = new ScaleTo(gameObject, targetScale, time);

	CommandManager::GetInstance().AddCommands(command);

	return 0;
}

int LuaManager::LuaSetGameObject(lua_State* L)
{
	int paramLength = lua_gettop(L);

	std::string gameObjectName = lua_tostring(L, 1);
	std::cout << "GameObject name :" << gameObjectName << std::endl;

	GetInstance().FindModelBasedOnName(gameObjectName);          // ModelName
	GetInstance().FindGameObjectBasedOnName(gameObjectName);     // GameObject

	return 0;
}

int LuaManager::LuaFollowObject(lua_State* L)
{
	int paramLength = lua_gettop(L);

	std::string followObjectName = lua_tostring(L, 1);
	float time = lua_tonumber(L, 2);

	float speed = static_cast<float>(lua_tonumber(L, 3));
	float acceleration = static_cast<float>(lua_tonumber(L, 4));
	float deceleration = static_cast<float>(lua_tonumber(L, 5));
	float distance = static_cast<float>(lua_tonumber(L, 6));

	float x = static_cast<float>(lua_tonumber(L, 7));
	float y = static_cast<float>(lua_tonumber(L, 8));
	float z = static_cast<float>(lua_tonumber(L, 9));

	glm::vec3 followOffset{ x,y,z };

	Model* targetModel = GetInstance().FindModel(followObjectName);

	GameObject* followGameObject = GetInstance().FindGameObject(followObjectName);

	Command* command = nullptr;

	command = new FollowObject(GetInstance().gameObject, followGameObject,time,speed, acceleration, deceleration, distance, followOffset);

	CommandManager::GetInstance().AddCommands(command);


	return 0;
}

int LuaManager::LuaSpawnGameObject(lua_State* L)
{
	int paramLength = lua_gettop(L);
	std::string GameObjectName = lua_tostring(L, 1);
	float time = static_cast<float>(lua_tonumber(L, 2));

	if (GameObjectName =="SphereTest")
	{
		
		
		
	}
	if (GameObjectName == "BARREL")
	{
		//GameObject* gameObject = new Barrel();

		Barrel*barrel = new Barrel();
		barrel->Start();
		barrel->model->transform.SetPosition(glm::vec3(20, -3, 5));
		barrel->model->isVisible = false;

		GetInstance().AddGameObjectInMap(barrel, "BARREL");

		Command* command = new SpawnObject(barrel, time);

		CommandManager::GetInstance().AddCommands(command);

	}
	else if(GameObjectName == "BARREL2")
	{
		Barrel* barrel2 = new Barrel();
		barrel2->Start();
		barrel2->model->id = "BARREL2";
		barrel2->SetGameObjectId(barrel2->model->id);
		barrel2->model->transform.SetPosition(glm::vec3(-20, -3, 5));
		barrel2->model->isVisible = false;

		GetInstance().AddGameObjectInMap(barrel2, "BARREL2");

		Command* command = new SpawnObject(barrel2, time);

		CommandManager::GetInstance().AddCommands(command);

	}


	

	

	return 0;
}

int LuaManager::LuaWaitForSeconds(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float waitTime = static_cast<float>(lua_tonumber(L, 1));

	Command* command = new WaitForSeconds(waitTime);
	
	CommandManager::GetInstance().AddCommands(command);
	return 0;
}

int LuaManager::LuaMoveAlongAxis(lua_State* L)
{
	int paramLength = lua_gettop(L);

	int axis = lua_tonumber(L, 1);

	float time = static_cast<float>(lua_tonumber(L, 2));
	float speed = static_cast<float>(lua_tonumber(L, 3));

	
	Model* model = GetInstance().model;

	Command* command = new MoveAlongAxisWithTime(model,axis,time,speed);

	CommandManager::GetInstance().AddCommands(command);


	return 0;
}

int LuaManager::LuaRotateAlongAxis(lua_State* L)
{
	int paramLength = lua_gettop(L);

	int axis = lua_tonumber(L, 1);

	float time = static_cast<float>(lua_tonumber(L, 2));
	float speed = static_cast<float>(lua_tonumber(L, 3));


	Model* model = GetInstance().model;

	Command* command = new RotateAlongAxisWithTime(model, axis, time, speed);

	CommandManager::GetInstance().AddCommands(command);


	return 0;
}

int LuaManager::LuaFollowWithTime(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float time = static_cast<float>(lua_tonumber(L, 1));

	GameObject* gameObject = GetInstance().gameObject;

	FollowCurveWithTime* command = new FollowCurveWithTime(gameObject, time);

	command->SetBezierCurve(new CubicBezierCurve());

	CommandManager::GetInstance().AddCommands(command);


	return 0;
}

int LuaManager::LuaAddPoint(lua_State* L)
{
	int paramLength = lua_gettop(L);

	FollowCurveWithTime* command = dynamic_cast<FollowCurveWithTime*>(CommandManager::GetInstance().CurrentCommand);


	if (paramLength>= 9)
	{
		glm::vec3 point;
		glm::vec3 controlPoint;
		glm::vec3 rotationOffset;

		point.x = luaL_checknumber(L, 1);
		point.y = luaL_checknumber(L, 2);
		point.z = luaL_checknumber(L, 3);

		controlPoint.x = luaL_checknumber(L, 4) + point.x;
		controlPoint.y = luaL_checknumber(L, 5) + point.y;
		controlPoint.z = luaL_checknumber(L, 6) + point.z;

		rotationOffset.x = luaL_checknumber(L, 7);
		rotationOffset.y = luaL_checknumber(L, 8);
		rotationOffset.z = luaL_checknumber(L, 9);

		command->AddPoint(point, controlPoint, rotationOffset);

		return 1;

	}
	else if (paramLength >= 6)
	{
		glm::vec3 point;
		glm::vec3 controlPoint;
		glm::vec3 rotationOffset = glm::vec3(0);

		point.x = luaL_checknumber(L, 1);
		point.y = luaL_checknumber(L, 2);
		point.z = luaL_checknumber(L, 3);

		controlPoint.x = luaL_checknumber(L, 4) + point.x;
		controlPoint.y = luaL_checknumber(L, 5) + point.y;
		controlPoint.z = luaL_checknumber(L, 6) + point.z;


		command->AddPoint(point, controlPoint, rotationOffset);

		//GetCurveTable(luaState);

		return 1;
	}


	return 0;
}

int LuaManager::LuaSetLookAtOffset(lua_State* L)
{
	int paramLength = lua_gettop(L);

	FollowCurveWithTime* command = dynamic_cast<FollowCurveWithTime*>(CommandManager::GetInstance().CurrentCommand);

	float x = static_cast<float>(lua_tonumber(L, 1));
	float y = static_cast<float>(lua_tonumber(L, 2));
	float z = static_cast<float>(lua_tonumber(L, 3));

	glm::vec3 lookAtOffset(x, y, z);


	command->SetLookAtOffset(lookAtOffset);


	return 0;
}

int LuaManager::LuaSetLookAtBool(lua_State* L)
{
	int paramLength = lua_gettop(L);

	FollowCurveWithTime* command = dynamic_cast<FollowCurveWithTime*>(CommandManager::GetInstance().CurrentCommand);

	int boolValue = lua_tonumber(L, 1);

	command->SetLookAtTangent((bool)boolValue);

	return 0;
}

int LuaManager::LuatLookAt(lua_State* L)
{
	int paramLength = lua_gettop(L);

	std::string lookAtObjectName = lua_tostring(L, 1);
	float time = static_cast<float>(lua_tonumber(L, 2));

	GameObject* lookAtGameObject = GetInstance().FindGameObject(lookAtObjectName);

	GameObject* currentGameObject = GetInstance().gameObject;

	std::cout << "Current Object :" << currentGameObject->id << std::endl;
	std::cout << "lookAtGameObject  :" << lookAtGameObject->id << std::endl;

	Command* command = new LookAt(currentGameObject, lookAtGameObject, time);

	CommandManager::GetInstance().AddCommands(command);

	return 0;
}

int LuaManager::LuaSetCollisionTrigger(lua_State* L)
{
	int paramLength = lua_gettop(L);

	int isTriggerTrue = lua_tonumber(L, 1);

	CommandGroup* currentGroup = CommandManager::GetInstance().currentCommandGroup;

	if (currentGroup!=nullptr)
	{
		currentGroup->isCollisionTrigger = false;
	}

	return 0;
}

int LuaManager::LuaPlaySound(lua_State* L)
{
	return 0;
}


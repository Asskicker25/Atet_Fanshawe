#pragma once
#include <string>
#include <iostream>
#include "PhysicsObject.h"
#include "Transform.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

struct PlayerMoveTo
{
	PhysicsObject* objPhysics;
	glm::vec3 objTransform;
	float easeIn;
	float easeOut;
	Transform transformObj;


};

struct Position
{
	float x;
	float y;
	float z;

	

};


class LuaBrain
{
public:
	LuaBrain();
	~LuaBrain();

	void LuaTestInit();
	PlayerMoveTo PlayerTransform();

	 Transform AssignTransform(Transform& transform);

	//Wrappers

	 static int lua_ExampleFunction(lua_State* L);

	
	 //

private:
	Transform transform;
	PlayerMoveTo posStruct;
	lua_State* L_state;
};


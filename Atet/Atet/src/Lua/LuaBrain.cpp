#include "LuaBrain.h"

LuaBrain::LuaBrain()
{
	/*posStruct.x = objPosition.position.x;
	posStruct.y = objPosition.position.y;
	posStruct.z = objPosition.position.z;*/
	
}

LuaBrain::~LuaBrain()
{
	//lua_close(this->L_state);
}


bool CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

int LuaBrain::lua_ExampleFunction(lua_State* L) 
{
	 
	
	float x = (int)lua_tonumber(L, 1);
	float y = (int)lua_tonumber(L, 2);
	float z = (int)lua_tonumber(L, 3);


	Transform* localTransform = new Transform(); // need something to assign the transform as this wrapper is static

	localTransform->position.x = x;
	localTransform->position.y = y;
	localTransform->position.z = z;
	
	std::cout << "transform Values are :" << localTransform->position.x << " , " << localTransform->position.y << " , "  << localTransform->position.z << std::endl;
	
	lua_pushnumber(L, localTransform->position.x);
	lua_pushnumber(L, localTransform->position.y);
	lua_pushnumber(L, localTransform->position.z);

	return 3;

}





void LuaBrain::LuaTestInit()
{

	std::string lua_script = "Example.lua";

	L_state = luaL_newstate();
	luaL_openlibs(L_state);
	lua_register(L_state, "MoveTransform", lua_ExampleFunction);

	if (CheckLua(L_state, luaL_dofile(L_state, lua_script.c_str())))
	{
		lua_getglobal(L_state, "MoveTo");

		if (lua_isfunction(L_state, -1))
		{
			lua_pushnumber(L_state, 5);
			lua_pushnumber(L_state, 8);
			lua_pushnumber(L_state, 15);
			

			if (CheckLua(L_state, lua_pcall(L_state, 3, 3, 0)))
			{
				std::cout << "Final Result : " << (int)lua_tonumber(L_state, 1) << " , " << (int)lua_tonumber(L_state, 2) << " , " << (int)lua_tonumber(L_state, 3) << std::endl;
			}


			
		}
	}

	

}

PlayerMoveTo LuaBrain::PlayerTransform()
{

	return PlayerMoveTo();
}

Transform LuaBrain::AssignTransform(Transform& transform)
{
	return this->transform = transform;
	
}


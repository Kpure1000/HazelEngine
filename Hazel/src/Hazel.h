#pragma once

//  ---Use by Hazel Application-----------
#include "Hazel/Core/Application.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Core/Time.h"
#include "Hazel/Debug/Instrumentor.h"
#include "Hazel/Utility/ThreadPool.h"
//  --------------------------------------

#ifdef CLIENT_ENTRY

//  ---Entry Point------------------------
#include "Hazel/Core/EntryPoint.h"
//  --------------------------------------

#endif // CLIENT_ENTRY

//  ---Input------------------------------
#include "Hazel/Core/Input.h"
//  --------------------------------------

//  ---Events-----------------------------
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
//  --------------------------------------

//  ---Render-----------------------------
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/Texture.h"
//  --------------------------------------

//  ---GUI--------------------------------
#include <imgui.h>
//  --------------------------------------

//  ---Graphics---------------------------
#include "Hazel/Graphics/Mesh/QuadMesh.h"
#include "Hazel/Graphics/Mesh/CubeMesh.h"
#include "Hazel/Graphics/Mesh/SphereMesh.h"
#include "Hazel/Graphics/Mesh/CircleMesh.h"
#include "Hazel/Graphics/Mesh/Sprite.h"
//  --------------------------------------

//  ---Controller-------------------------
#include "Hazel/OrthographicCameraController.h"
//  --------------------------------------

//  ---Layer------------------------------
#include "Hazel/Core/Layer.h"
//  --------------------------------------

//  ---Platform---------------------------

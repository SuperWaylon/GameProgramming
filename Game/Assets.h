#pragma once
#include "Model.h"
#include <memory>

namespace assets
{
	extern std::shared_ptr<nu::Model> pmodel;
	extern std::shared_ptr<nu::Model> thrusterModel;
	extern std::shared_ptr<nu::Model> emodel;
	extern std::shared_ptr<nu::Model> bmodel;
}
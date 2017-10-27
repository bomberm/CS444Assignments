#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "Philosopher.h"
#include "Fork.h"
#include "helperFunctions.h"

enum pflag {
	THINK,
	HUNGRY,
	EAT
};

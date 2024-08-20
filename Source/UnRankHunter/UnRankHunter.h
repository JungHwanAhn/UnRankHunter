// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#pragma region [KYG Log]

// New Log Category
DECLARE_LOG_CATEGORY_EXTERN(UH_LogDefault, Log, All);

#define UH_CALLINFO (*FString::Printf(TEXT("%s(%d)"), *FString(__FUNCTION__), __LINE__))
#define UH_Log(category, verbosity, fmt, ...) UE_LOG(category, verbosity, TEXT("%s %s"), UH_CALLINFO, *FString::Printf(fmt, ##__VA_ARGS__))
#define UH_LogTemp(verbosity, fmt) UH_Log(UH_LogDefault, verbosity, fmt)
#define UH_LogTempParam(verbosity, fmt, ...) UH_Log(UH_LogDefault, verbosity, fmt, ##__VA_ARGS__)
#define UH_LogWarning(fmt, ...) UH_Log(Warning, fmt, ##__VA_ARGS__)
#define UH_LogError(fmt, ...) UH_Log(Error, fmt, ##__VA_ARGS__)

#pragma endregion
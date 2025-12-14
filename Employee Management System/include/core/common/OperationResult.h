#pragma once
#include "OperationStatus.h"
#include<string>
#include<optional>
using namespace std;


template <typename T>
struct OperationResult
{
	OperationStatus status;
	string message;
	optional<T> data;

	static OperationResult<T> Success(T value, const string& message = "")
	{
		return { OperationStatus::Success, message, move(value) };
	}

	static OperationResult<T> Failure(const string& message)
	{
		return { OperationStatus::Failure, message, nullopt };
	}

	static OperationResult<T> NoChanges(const string& message)
	{
		return { OperationStatus::NoChanges, message, nullopt };
	}
};

template <>
struct OperationResult<void>
{
	OperationStatus status;
	string message;

	static OperationResult Success(const string& message = "")
	{
		return { OperationStatus::Success, message };
	}

	static OperationResult Failure(const string& message)
	{
		return { OperationStatus::Failure, message };
	}

	static OperationResult NoChanges(const string& message)
	{
		return { OperationStatus::NoChanges, message };
	}
};
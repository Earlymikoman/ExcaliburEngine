/*********************************************************************
 * @file   System.h
 * @brief  .
 * 
 * Project: Excalibur
 * 
 * @author Xander Boosinger (xboosinger@gmail.com)
 * @date   April 2025
 * 
 *********************************************************************
/*
 *			*	/\
 *			   / /	*
 *		*	__/ /__
 *		      /	  *
 *			 /
 */

#pragma once

class Message;

class System
{
protected:

	System() = default;

private:

	System(System const& rhs) = delete;

	System& operator=(System const& rhs) = delete;

	virtual void SingletonReminder() = 0;

public:

	virtual void Init(){}

	virtual void Update(double& dt) { dt; }

	virtual void Render(){}

	virtual void Exit(){}

	virtual void HandleMessage(Message* message) { message; }

};

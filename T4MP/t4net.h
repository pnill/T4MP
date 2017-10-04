#pragma once
#define _WINSOCKAPI_ 
#include <winsock2.h>
#include <vector>
#include "T4Engine.h"
#include "t4mp.pb.h"



class NetworkPlayer
{
	public:
		u_long ipaddr = 0;
		u_short port = 0;
		int index = 0;

		bool crouch_set = false;
		bool jump_set = false;

		bool fire_set = false;
		bool fire_hold = false;
		float fire_hold_time = 0.0f;
		bool fire_release = false;
		bool fire_release_time = 0.0f;
};

class T4Network
{
	int local_index = 0;
	int weapon_switch_attempts = 0;
	int last_player_index = 0;

	SOCKET serverSock = INVALID_SOCKET;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	std::vector<NetworkPlayer*> netplayers;
	LPCSTR server_ip = new char[22];
	
	u_short port = 27004;
	bool AddPlayer(u_long, u_short);

public:
	bool fire_set = false;
	bool fire_hold = false;
	bool fire_release = false;
	float fire_hold_time = 0.0f;
	float fire_release_time = 0.0f;

	bool server = false;
	bool connected = false;

	void Initalize();
	void ConnectToServer();
	void ProcessMessage();
	void Destroy();
	void SendSnapShot();
	void SendPlayerSnapShot();
	void ProcessServerSnap(const ServerSnap &pSeverSnap);
	void ProcessPlayerSnap(const PlayerSnap &pPlayerSnap, u_long pIP, u_short pPort);


};
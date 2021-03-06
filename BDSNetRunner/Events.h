#pragma once
#include "BDS.hpp"

enum EventType : UINT16 {
	Nothing = 0,
	onServerCmd = 1,
	onServerCmdOutput = 2,
	onFormSelect = 3,
	onUseItem = 4,
	onPlacedBlock = 5,
	onDestroyBlock = 6,
	onStartOpenChest = 7,
	onStartOpenBarrel = 8,
	onStopOpenChest = 9,
	onStopOpenBarrel = 10,
	onSetSlot = 11,
	onChangeDimension = 12,
	onMobDie = 13,
	onMobHurt = 14,
	onRespawn = 15,
	onChat = 16,
	onInputText = 17,
	onCommandBlockUpdate = 18,
	onInputCommand = 19,
	onBlockCmd = 20,
	onNpcCmd = 21,
	onLoadName = 22,
	onPlayerLeft = 23,
	onMove = 24,
	onAttack = 25,
	onLevelExplode = 26
};

// 监听模式
static enum ActMode : UINT16
{
	BEFORE = 0,
	AFTER = 1
};

// 所有关键字
struct ACTEVENT {
	const std::string ONSERVERCMD = u8"onServerCmd";
	const std::string ONSERVERCMDOUTPUT = u8"onServerCmdOutput";
	const std::string ONFORMSELECT = u8"onFormSelect";
	const std::string ONUSEITEM = u8"onUseItem";
	const std::string ONMOVE = u8"onMove";
	const std::string ONATTACK = u8"onAttack";
	const std::string ONPLACEDBLOCK = u8"onPlacedBlock";
	const std::string ONDESTROYBLOCK = u8"onDestroyBlock";
	const std::string ONSTARTOPENCHEST = u8"onStartOpenChest";
	const std::string ONSTARTOPENBARREL = u8"onStartOpenBarrel";
	const std::string ONCHANGEDIMENSION = u8"onChangeDimension";
	const std::string ONLOADNAME = u8"onLoadName";
	const std::string ONPLAYERLEFT = u8"onPlayerLeft";
	const std::string ONSTOPOPENCHEST = u8"onStopOpenChest";
	const std::string ONSTOPOPENBARREL = u8"onStopOpenBarrel";
	const std::string ONSETSLOT = u8"onSetSlot";
	const std::string ONMOBDIE = u8"onMobDie";
	const std::string ONRESPAWN = u8"onRespawn";
	const std::string ONCHAT = u8"onChat";
	const std::string ONINPUTTEXT = u8"onInputText";
	const std::string ONINPUTCOMMAND = u8"onInputCommand";
	const std::string ONLEVELEXPLODE = u8"onLevelExplode";
};

struct Events {
	EventType type;	// 事件类型
	ActMode mode;	// 触发模式
	int result;		// 事件结果（注册After事件时，此值有效）
	void* data;		// 原始数据指针
};

struct ServerCmdEvent {
	char* cmd;	// 指令数据
public:
	ServerCmdEvent() {
		memset(this, 0, sizeof(ServerCmdEvent));
	}
	void releaseAll() {
		if (cmd) {
			delete cmd;
			cmd = NULL;
		}
	}
};

struct ServerCmdOutputEvent {
	char* output;	// 输出信息
public:
	ServerCmdOutputEvent() {
		memset(this, 0, sizeof(ServerCmdOutputEvent));
	}
	void releaseAll() {
		if (output) {
			delete output;
			output = NULL;
		}
	}
};

struct PlayerEvent {
	char* playername;	// 玩家名字
	char* dimension;	// 玩家所在维度
	Vec3 XYZ;			// 玩家所处位置
	int dimensionid;	// 玩家所在维度ID
	bool isstand;		// 玩家是否立足于方块/悬空
public:
	PlayerEvent() {
		memset(this, 0, sizeof(PlayerEvent));
	}
	void releaseAll() {
		if (playername) {
			delete playername;
			playername = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
	}
};

struct FormSelectEvent : PlayerEvent {
	char* uuid;			// 玩家uuid信息
	char* selected;		// 表单回传的选择项信息
	int formid;			// 表单ID
public:
	FormSelectEvent() {
		memset(this, 0, sizeof(FormSelectEvent));
	}
	void releaseAll() {
		if (uuid) {
			delete uuid;
			uuid = NULL;
		}
		if (selected) {
			delete selected;
			selected = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct UseItemEvent : PlayerEvent {
	char* itemname;		// 物品名称
	BPos3 position;		// 操作方块所在位置
	short itemid;		// 物品ID
	short itemaux;		// 物品特殊值
public:
	UseItemEvent() {
		memset(this, 0, sizeof(UseItemEvent));
	}
	void releaseAll() {
		if (itemname) {
			delete itemname;
			itemname = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct BlockEvent : PlayerEvent {
	char* blockname;	// 方块名称
	BPos3 position;		// 操作方块所在位置
	short blockid;		// 方块ID
public:
	BlockEvent() {
		memset(this, 0, sizeof(BlockEvent));
	}
	void releaseAll() {
		if (blockname) {
			delete blockname;
			blockname = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct PlacedBlockEvent : BlockEvent {
};

struct DestroyBlockEvent : BlockEvent {
};

struct StartOpenChestEvent : BlockEvent {
};

struct StartOpenBarrelEvent : BlockEvent {
};

struct StopOpenChestEvent : BlockEvent {
};

struct StopOpenBarrelEvent : BlockEvent {
};

struct SetSlotEvent : PlayerEvent {
	char* itemname;		// 物品名字
	char* blockname;	// 方块名称
	BPos3 position;		// 操作方块所在位置
	int itemcount;		// 物品数量
	int slot;			// 操作格子位置
	short itemaux;		// 物品特殊值
	short blockid;		// 方块ID
	short itemid;		// 物品ID
	
public:
	SetSlotEvent() {
		memset(this, 0, sizeof(SetSlotEvent));
	}
	void releaseAll() {
		if (itemname) {
			delete itemname;
			itemname = NULL;
		}
		if (blockname) {
			delete blockname;
			blockname = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};


struct ChangeDimensionEvent : PlayerEvent {
};

struct MobDieEvent {
	char* mobname;		// 生物名称
	char* playername;	// 玩家名字（若为玩家死亡，附加此信息）
	char* dimension;	// 玩家所在维度（附加信息）
	char* mobtype;		// 生物类型
	char* srcname;		// 伤害源名称
	char* srctype;		// 伤害源类型
	Vec3 XYZ;			// 生物所在位置
	int dimensionid;	// 生物所处维度ID
	int dmcase;			// 伤害具体原因ID
	bool isstand;		// 玩家是否立足于方块/悬空（附加信息）
public:
	MobDieEvent() {
		memset(this, 0, sizeof(MobDieEvent));
	}
	void releaseAll() {
		if (mobname) {
			delete mobname;
			mobname = NULL;
		}
		if (playername) {
			delete playername;
			playername = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
		if (mobtype) {
			delete mobtype;
			mobtype = NULL;
		}
		if (srcname) {
			delete srcname;
			srcname = NULL;
		}
		if (srctype) {
			delete srctype;
			srctype = NULL;
		}
	}
};

struct MobHurtEvent : MobDieEvent {
	char* dmtype;	// 生物受伤类型
	float health;	// 生物血量
	int dmcount;	// 生物受伤具体值
public:
	MobHurtEvent() {
		memset(this, 0, sizeof(MobHurtEvent));
	}
	void releaseAll() {
		if (dmtype) {
			delete dmtype;
			dmtype = NULL;
		}
		((MobDieEvent*)this)->releaseAll();
	}
};

struct RespawnEvent : PlayerEvent {
};

struct ChatEvent {
	char* playername;	// 发言人名字（可能为服务器或命令方块发言）
	char* target;		// 接收者名字
	char* msg;			// 接收到的信息
	char* chatstyle;	// 聊天类型
public:
	ChatEvent() {
		memset(this, 0, sizeof(ChatEvent));
	}
	void releaseAll() {
		if (playername) {
			delete playername;
			playername = NULL;
		}
		if (target) {
			delete target;
			target = NULL;
		}
		if (msg) {
			delete msg;
			msg = NULL;
		}
		if (chatstyle) {
			delete chatstyle;
			chatstyle = NULL;
		}
	}
};

struct InputTextEvent : PlayerEvent {
	char* msg;	// 输入的文本
public:
	InputTextEvent() {
		memset(this, 0, sizeof(InputTextEvent));
	}
	void releaseAll() {
		if (msg) {
			delete msg;
			msg = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct CommandBlockUpdateEvent : PlayerEvent {
	char* cmd;		// 将被更新的新指令
	char* actortype;// 实体类型（若被更新的是非方块，附加此信息）
	BPos3 position;	// 命令方块所在位置
	bool isblock;	// 是否是方块
public:
	CommandBlockUpdateEvent() {
		memset(this, 0, sizeof(CommandBlockUpdateEvent));
	}
	void releaseAll() {
		if (cmd) {
			delete cmd;
			cmd = NULL;
		}
		if (actortype) {
			delete actortype;
			actortype = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct InputCommandEvent : PlayerEvent {
	char* cmd;	// 玩家输入的指令
public:
	InputCommandEvent() {
		memset(this, 0, sizeof(InputCommandEvent));
	}
	void releaseAll() {
		if (cmd) {
			delete cmd;
			cmd = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct BlockCmdEvent {
	char* cmd;		// 将被执行的指令
	char* name;		// 执行者自定义名称
	char* dimension;// 命令块所处维度
	BPos3 position;	// 执行者所在位置
	int dimensionid;// 命令块所处维度ID
	int tickdelay;	// 命令设定的间隔时间
	int type;		// 执行者类型
public:
	BlockCmdEvent() {
		memset(this, 0, sizeof(BlockCmdEvent));
	}
	void releaseAll() {
		if (cmd) {
			delete cmd;
			cmd = NULL;
		}
		if (name) {
			delete name;
			name = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
	}
};

struct NpcCmdEvent {
	char* npcname;		// NPC名字
	char* entity;		// NPC实体标识名
	char* dimension;	// NPC所处维度
	char* actions;		// 指令列表
	Vec3 position;		// NPC所在位置
	int actionid;		// 选择项
	int entityid;		// NPC实体标识ID
	int dimensionid;	// NPC所处维度ID
public:
	NpcCmdEvent() {
		memset(this, 0, sizeof(NpcCmdEvent));
	}
	void releaseAll() {
		if (npcname) {
			delete npcname;
			npcname = NULL;
		}
		if (entity) {
			delete entity;
			entity = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
		if (actions) {
			delete actions;
			actions = NULL;
		}
	}
};

struct LoadNameEvent {
	char* playername;	// 玩家名字
	char* uuid;			// 玩家uuid字符串
	char* xuid;			// 玩家xuid字符串
	char* ability;		// 玩家能力值列表（可选，商业版可用）
public:
	LoadNameEvent() {
		memset(this, 0, sizeof(LoadNameEvent));
	}
	void releaseAll() {
		if (playername) {
			delete playername;
			playername = NULL;
		}
		if (uuid) {
			delete uuid;
			uuid = NULL;
		}
		if (xuid) {
			delete xuid;
			xuid = NULL;
		}
		if (ability) {
			delete ability;
			ability = NULL;
		}
	}
};

struct PlayerLeftEvent : LoadNameEvent {
};

struct MoveEvent : PlayerEvent {
};

struct AttackEvent : PlayerEvent
{
	char* actorname;	// 被攻击实体名称
	char* actortype;	// 被攻击实体类型
	Vec3 actorpos;		// 被攻击实体所处位置
public:
	AttackEvent() {
		memset(this, 0, sizeof(AttackEvent));
	}
	void releaseAll() {
		if (actorname) {
			delete actorname;
			actorname = NULL;
		}
		if (actortype) {
			delete actortype;
			actortype = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct LevelExplodeEvent {
	char* entity;		// 爆炸者实体标识名（可能为空）
	char* blockname;	// 爆炸方块名（可能为空）
	char* dimension;	// 爆炸者所处维度
	Vec3 position;		// 爆炸点所在位置
	int entityid;		// 爆炸者实体标识ID
	int dimensionid;	// 爆炸者所处维度ID
	float explodepower;	// 爆炸强度
	short blockid;		// 爆炸方块ID
public:
	LevelExplodeEvent() {
		memset(this, 0, sizeof(LevelExplodeEvent));
	}
	void releaseAll() {
		if (entity) {
			delete entity;
			entity = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
	}
};
#pragma once
#include <string>
#include <memory>

enum class OriginType : char {
	Player = 0,
	Block = 1,
	MinecartBlock = 2,
	DevConsole = 3,
	Test = 4,
	AutomationPlayer = 5,
	ClientAutomation = 6,
	DedicatedServer = 7,
	Actor = 8,
	Virtual = 9,
	GameArgument = 10,
	ActorServer = 11
};

class CommandOrigin {
public:
	CommandOrigin(CommandOrigin const&) = delete;
	virtual ~CommandOrigin() = 0;
	virtual std::string& getRequestId() const = 0;
	virtual std::string getName() const = 0;
	virtual Vec3* getBlockPosition(Vec3*) const = 0;
	virtual Vec3 getWorldPosition() const = 0;
	virtual VA getLevel() const = 0;		// Level* getLevel() const
	virtual Dimension* getDimension() const = 0;
	virtual Actor* getEntity() const = 0;
	virtual VA getPermissionsLevel() const = 0;	// enum CommandPermissionLevel getPermissionsLevel() const
	virtual std::unique_ptr<CommandOrigin> clone() const = 0;
	virtual bool unk1() const = 0;
	virtual bool unk2() const = 0;
	virtual bool hasChatPerms() const = 0;
	virtual bool hasTellPerms() const = 0;
	virtual bool canUseAbility(VA) const = 0;		// bool canUseAbility(AbilitiesIndex) const
	virtual bool isWorldBuilder() const = 0;
	virtual bool canUseCommandsWithoutCheatsEnabled() const = 0;
	virtual bool isSelectorExpansionAllowed() const = 0;
	virtual VA getSourceId_net() const = 0;			// NetworkIdentifier getSourceId_net() const
	virtual char getSourceSubId() const = 0;
	virtual CommandOrigin* getOutputReceiver() const = 0;
	virtual OriginType getOriginType() const = 0;
	virtual void toCommandOriginData_stub() const = 0;
	virtual VA const& getUUID() const = 0;			// mce::UUID const& getUUID() const
	virtual void handleCommandOutputCallback_stub(void*) = 0;
	virtual void _setUUID(VA const&) = 0;			// void _setUUID(mce::UUID const&)
};

class CommandContext {
public:
	std::string CMD;
	CommandOrigin* Ori;
	int Version = 10;
	std::string& getCmd() {
		return CMD;
	}
	class CommandOrigin& getOrigin() {
		return *Ori;
	}
};

struct BaseCommandBlock {
	std::string mLastOutputId;
	std::vector<std::string> mLastOutputParams;
	std::string mCommand;
	std::string mName;
	VA mCompiledCommand;
	VA mLastExecution;
	int mVersion;
	int mSuccessCount;
	int mTickDelay;
	char mExecuteOnFirstTick;
	char mTrackOutput;
	char uk[2];
public:
	std::string getCmd() {						// IDA BaseCommandBlock::save
		return *(std::string *)((VA)this + 56);
	}
	std::string getName() {
		return *(std::string*)((VA)this + 88);
	}
	int getTickDelay() {
		return *((int*)this + 36);
	}
};
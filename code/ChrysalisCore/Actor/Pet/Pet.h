#pragma once


namespace Chrysalis
{
/**
A CPetComponent is an actor that represents a pet within the game.
**/
// TODO: probably needs to also implement IInventoryListener to listen for inventory changes.

class CPetComponent
	: public IEntityComponent
{
protected:
	friend CChrysalisCorePlugin;
	static void Register(Schematyc::CEnvRegistrationScope& componentScope);

	// IEntityComponent
	void Initialize() override;
	void ProcessEvent(SEntityEvent& event) override;
	uint64 GetEventMask() const { return BIT64(ENTITY_EVENT_UPDATE); }
	// ~IEntityComponent

public:
	CPetComponent() {}
	virtual ~CPetComponent() {}

	static void ReflectType(Schematyc::CTypeDesc<CPetComponent>& desc);

	static CryGUID& IID()
	{
		static CryGUID id = "{03DCFDAE-6F31-41D3-9FF5-26F79BB04278}"_cry_guid;
		return id;
	}

	/** Resets the character to an initial state. */
	virtual void OnResetState();
};
}
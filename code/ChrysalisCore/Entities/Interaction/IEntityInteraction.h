#pragma once

#include <CryCore/Platform/platform.h>


namespace Chrysalis
{
class IActorComponent;


/** An generic definition for interactions fired off by the player during gameplay. */
struct IInteraction
{
	/**
	Called at the start of an interaction. Generally called on a downward keypress.
	
	\param [in,out]	actor The actor who triggered this interaction.
	**/
	virtual void OnInteractionStart(IActorComponent& actor) {};


	/**
	Called each game frame an interaction is ongoing. This will be called multiple times, as long as the player is
	holding down the interaction key / button.
	
	\param [in,out]	actor The actor who triggered this interaction.
	**/
	virtual void OnInteractionTick(IActorComponent& actor) {};


	/**
	Called when an interaction is completed normally. Generally called on an upward keypress.
	
	\param [in,out]	actor The actor who triggered this interaction.
	**/
	virtual void OnInteractionComplete(IActorComponent& actor) {};


	/**
	Called if an interaction is cancelled early. This might, for instance, be called if the player hits ESC while
	still holding down the interaction key / button. It's unlikely to be needed and is only provided for completeness.
	
	\param [in,out]	actor The actor who triggered this interaction.
	**/
	virtual void OnInteractionCancel(IActorComponent& actor) {};

	bool IsUseable() const { return true; };
	virtual const string GetVerb() const { return "interaction_interact"; };
	virtual const string GetVerbUI() const { return "@" + GetVerb(); };

	bool IsEnabled() const { return m_isEnabled; };
	void SetEnabled(bool isEnabled) { m_isEnabled = isEnabled; };
	bool IsHidden() const { return m_isHidden; };
	void SetHidden(bool isHidden) { m_isHidden = isHidden; };

protected:
	bool m_isEnabled { true };
	bool m_isHidden { false };
};
DECLARE_SHARED_POINTERS(IInteraction);


// ***
// *** Zoom in to an entity and switch to an examine camera.
// ***

struct IInteractionExamine
{
	virtual void OnInteractionExamineStart(IActorComponent& actor) = 0;
	virtual void OnInteractionExamineComplete(IActorComponent& actor) = 0;
	virtual void OnInteractionExamineCancel(IActorComponent& actor) = 0;
};


class CInteractionExamine : public IInteraction
{
public:
	CInteractionExamine(IInteractionExamine* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_examine"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionExamineStart(actor); };
	void OnInteractionComplete(IActorComponent& actor) override { m_subject->OnInteractionExamineComplete(actor); };
	void OnInteractionCancel(IActorComponent& actor) override { m_subject->OnInteractionExamineCancel(actor); };

private:
	IInteractionExamine* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionExamine);


// ***
// *** Generic interactions e.g. "use", "interact". Good for when then is really only one
// *** option for interacting with an entity.
// ***

struct IInteractionInteract
{
	virtual void OnInteractionInteractStart(IActorComponent& actor) = 0;
	virtual void OnInteractionInteractTick(IActorComponent& actor) = 0;
	virtual void OnInteractionInteractComplete(IActorComponent& actor) = 0;
	virtual void OnInteractionInteractCancel(IActorComponent& actor) = 0;
};


class CInteractionInteract : public IInteraction
{
public:
	CInteractionInteract(IInteractionInteract* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_interact"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionInteractStart(actor); };
	void OnInteractionTick(IActorComponent& actor) override { m_subject->OnInteractionInteractTick(actor); };
	void OnInteractionComplete(IActorComponent& actor) override { m_subject->OnInteractionInteractComplete(actor); };
	void OnInteractionCancel(IActorComponent& actor) override { m_subject->OnInteractionInteractCancel(actor); };

private:
	IInteractionInteract* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionInteract);


// ***
// *** Trigger a DRS operation with variable passed in from the component.
// ***

struct IInteractionDRS
{
	virtual void OnInteractionDRS() = 0;
};


class CInteractionDRS : public IInteraction
{
public:
	CInteractionDRS(IInteractionDRS* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_drs"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionDRS(); };

private:
	IInteractionDRS* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionDRS);


// ***
// *** Switches
// ***

struct IInteractionSwitch
{
	virtual void OnInteractionSwitchToggle(IActorComponent& actor) = 0;
	virtual void OnInteractionSwitchOff(IActorComponent& actor) = 0;
	virtual void OnInteractionSwitchOn(IActorComponent& actor) = 0;
};


class CInteractionSwitchToggle : public IInteraction
{
public:
	CInteractionSwitchToggle(IInteractionSwitch* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_switch_toggle"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionSwitchToggle(actor); };

private:
	IInteractionSwitch* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionSwitchToggle);


class CInteractionSwitchOn : public IInteraction
{
public:
	CInteractionSwitchOn(IInteractionSwitch* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_switch_on"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionSwitchOn(actor); };

private:
	IInteractionSwitch* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionSwitchOn);


class CInteractionSwitchOff : public IInteraction
{
public:
	CInteractionSwitchOff(IInteractionSwitch* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_switch_off"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionSwitchOff(actor); };

private:
	IInteractionSwitch* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionSwitchOff);


// ***
// *** Items which can be pickup up, inspected, dropped, etc.
// ***


struct IInteractionItem
{
	virtual void OnInteractionItemInspect(IActorComponent& actor) = 0;
	virtual void OnInteractionItemPickup(IActorComponent& actor) = 0;
	virtual void OnInteractionItemDrop(IActorComponent& actor) = 0;
	virtual void OnInteractionItemToss(IActorComponent& actor) = 0;
};


class CInteractionItemInspect : public IInteraction
{
public:
	CInteractionItemInspect(IInteractionItem* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_inspect"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionItemInspect(actor); };

private:
	IInteractionItem* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionItemInspect);


class CInteractionItemPickup : public IInteraction
{
public:
	CInteractionItemPickup(IInteractionItem* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_pickup"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionItemPickup(actor); };

private:
	IInteractionItem* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionItemPickup);


class CInteractionItemDrop : public IInteraction
{
public:
	CInteractionItemDrop(IInteractionItem* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_drop"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionItemDrop(actor); };

private:
	IInteractionItem* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionItemDrop);


class CInteractionItemToss : public IInteraction
{
public:
	CInteractionItemToss(IInteractionItem* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_toss"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionItemToss(actor); };

private:
	IInteractionItem* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionItemToss);


// ***
// *** Generic open.
// ***


struct IInteractionOpenable
{
	virtual void OnInteractionOpenableOpen(IActorComponent& actor) = 0;
	virtual void OnInteractionOpenableClose(IActorComponent& actor) = 0;
};


class CInteractionOpenableOpen : public IInteraction
{
public:
	CInteractionOpenableOpen(IInteractionOpenable* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_openable_open"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionOpenableOpen(actor); };

private:
	IInteractionOpenable* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionOpenableOpen);


class CInteractionOpenableClose : public IInteraction
{
public:
	CInteractionOpenableClose(IInteractionOpenable* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_openable_close"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionOpenableClose(actor); };

private:
	IInteractionOpenable* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionOpenableClose);


// ***
// *** Lockable.
// ***


struct IInteractionLockable
{
	virtual void OnInteractionLockableLock(IActorComponent& actor) = 0;
	virtual void OnInteractionLockableUnlock(IActorComponent& actor) = 0;
};


class CInteractionLockableLock : public IInteraction
{
public:
	CInteractionLockableLock(IInteractionLockable* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_lockable_lock"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionLockableLock(actor); };

private:
	IInteractionLockable* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionLockableLock);


class CInteractionLockableUnlock : public IInteraction
{
public:
	CInteractionLockableUnlock(IInteractionLockable* subject, bool isEnabled = true, bool isHidden = false)
	{
		m_subject = subject;
		m_isEnabled = isEnabled;
		m_isHidden = isHidden;
	};

	const string GetVerb() const override { return "interaction_lockable_unlock"; };
	void OnInteractionStart(IActorComponent& actor) override { m_subject->OnInteractionLockableUnlock(actor); };

private:
	IInteractionLockable* m_subject { nullptr };
};
DECLARE_SHARED_POINTERS(CInteractionLockableUnlock);
}
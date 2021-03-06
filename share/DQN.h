#pragma once 

//#include "Replay.h"
#include "PEReplay.h"

const float DEFAULT_EPSILON = 0.20f;
const float MAX_EPSILON = 0.40f;
const float MIN_EPSILON = 0.10f;
const float EPSILON_DECAY_RATE = 0.9999f;
const float DEFAULT_LEARNING_RATE = 0.95f;

//const int DEFAULT_EPOCH_RATE = 3;

/**
 *   Deep Q-Network
 */
class DQN {
public:
	DQN();
	~DQN(){}
	virtual void initialize(std::shared_ptr<network<sequential>>& nn_ptr);
	void setLearnigRate(float gamma){gamma_ = gamma;}
	virtual void update(PEReplay& replay, size_t batch_size, size_t epochs = 1);
	label_t selectAction(const vec_t& state, bool is_greedy = false);
	vec_t forward(const vec_t& state_vector);
	void printQValues(const vec_t& state_vector);
	float getTD(label_t& action, float& reward, vec_t& s1, vec_t& s2);

	network<sequential>& getNetwork() { return *nn_ptr_.get();}
protected:
	float getMaxQ(vec_t& q);
	label_t getMaxQIdx(vec_t& q);
	void backwardDueling(float& newQval);
	
protected:
	std::shared_ptr<network<sequential>> nn_ptr_;
	float gamma_;
	float epsilon_;
};

/**
 *   Double Deep Q-Network
 */
class DDQN: public DQN {
public:
	DDQN();
	~DDQN(){}
	void update(PEReplay& replay, size_t batch_size, size_t epochs = 1);
	void initialize(std::shared_ptr<network<sequential>>& nn_ptr);
protected:
	std::shared_ptr<network<sequential>> target_nn_ptr_;
};

// end of file

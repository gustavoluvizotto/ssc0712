#ifndef STATE_H
#define	STATE_H
template <class T1> class State {
public:

    State() {}
    virtual ~State() {}
    
    virtual void Enter(T1*) = 0;
    virtual void Execute(T1*) = 0;
    virtual void Exit(T1*) = 0;
};

#endif	/* STATE_H */
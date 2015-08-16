#include "HelloWorldScene.h"

#define PTM_RATIO 32.0 // 32.0px = 1m in Box2D.

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //////////////////////////////
    // 2. Initialize Box2D.
    
    // init world.
    b2Vec2 gravity = b2Vec2(0, -9.8f);
    m_world     = new b2World(gravity);
    m_debugDraw = new GLESDebugDraw(PTM_RATIO);
    m_world->SetDebugDraw(m_debugDraw);
    
    // Set flags of debug draw.
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    // flags += b2Draw::e_jointBit;
    // flags += b2Draw::e_aabbBit;
    // flags += b2Draw::e_pairBit;
    // flags += b2Draw::e_centerOfMassBit;
    m_debugDraw->SetFlags(flags);
    
    // init floor.
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(visibleSize.width / 2 / PTM_RATIO, 0);
        b2Body* body = m_world->CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(visibleSize.width / 2 / PTM_RATIO, 16 / PTM_RATIO);
        body->CreateFixture(&shape, 0);
    }
    
    // init box.
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(visibleSize.width / 2 / PTM_RATIO, visibleSize.height / 2 / PTM_RATIO);
        b2Body* body = m_world->CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(16 / PTM_RATIO, 16 / PTM_RATIO);
        body->CreateFixture(&shape, 0);
    }
    
    scheduleUpdate(); // Called update method.
    
    return true;
}


void HelloWorld::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    
    log("hoge");
    
    m_world->Step(dt, velocityIterations, positionIterations);
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Layer::draw(renderer, transform, flags);
    
    // Draw debug for Box2D.
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    kmGLPushMatrix();
    m_world->DrawDebugData();
    kmGLPopMatrix();
}

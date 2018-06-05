//
//  DesignModel-Create.h
//  my_Account
//
//  Created by hubao on 2018/5/21.
//  Copyright © 2018年 cltx. All rights reserved.
//

#ifndef DesignModel_Create_h
#define DesignModel_Create_h

#include <mutex>

/*
 ************************************************************************************************
 * 单例模式 - 懒汉式（双检锁 DCL 机制）
 ************************************************************************************************
 */
namespace SingletonPattern{
    // 单例模式 - 懒汉式（双检锁 DCL 机制）- 手动释放
    class Singleton{
    public:
        static Singleton* getInstance(){
            if(mpInstance == NULL){
                std::lock_guard<std::mutex> lock(m_mutex);
                if(mpInstance == NULL){
                    mpInstance = new Singleton();
                }
            }
            return mpInstance;
        }
        
        static void Destory(){
            if (mpInstance != NULL) {
                delete mpInstance;
                mpInstance = NULL;
            }
        }
    private:
        Singleton(){}
        
    private:
        static Singleton* mpInstance;
        static mutex m_mutex;
    };
    
    Singleton *Singleton::mpInstance = NULL;
    mutex Singleton::m_mutex;
    
    //单例模式 - 懒汉式（双检锁 DCL 机制）- 自动释放
    class CSingleton{
    public:
        static CSingleton* GetInstance(){
            if(mpInstance == NULL){
                std::lock_guard<std::mutex> lock(m_mutex);
                if(mpInstance == NULL){
                    mpInstance = new CSingleton();
                }
            }
            return mpInstance;
        }
        
    private:
        CSingleton() {}
        
    private:
        static CSingleton *mpInstance;
        static mutex m_mutex;
        
        class GC
        {
        public:
            ~GC()
            {
                if (mpInstance != NULL) {
                    delete mpInstance;
                    mpInstance = NULL;
                }
            }
            static GC gc;
        };
    };
    
    CSingleton *CSingleton::mpInstance = NULL;
    mutex CSingleton::m_mutex;
}

/*
 ************************************************************************************************
 * 抽象工厂模式
 ************************************************************************************************
 */
namespace AbstractFactory
{
    class ICar{};
    class BenzCar : public ICar{};
    class AudiCar : public ICar{};
    
    class IFactory{
    public:
        virtual ICar* createCar() = 0;
        static IFactory* createFactory(int type=0);
    };
    
    class BenzFactory : public IFactory{
        ICar* createCar() {
            cout << "Benz Car" << endl;
            return new BenzCar;
        }
    };
    
    class AudiFactory : public IFactory{
        ICar* createCar() {
            cout << "Audi Car" << endl;
            return new AudiCar;
        }
    };
    
    IFactory* IFactory::createFactory(int type){
        IFactory* aFactory = NULL;
        
        if(type == 0 ) aFactory = new BenzFactory;
        else aFactory = new AudiFactory;
        return aFactory;
    }
    //     ****************************** 示例代码 ******************************
    //    IFactory *benz = IFactory::createFactory(0);
    //    benz->createCar();
    //    IFactory *audi = IFactory::createFactory(1);
    //    audi->createCar();
}

/*
 ************************************************************************************************
 * 建造者模式
 ************************************************************************************************
 */
namespace BuilderPattern {
    class IBuilder{
    public:
        virtual void BuildCpu() = 0;
        virtual void BuildMainboard() = 0;
    };
    
    class ThinkPadBuilder{
    public:
        void BuildCpu(){
            cout << "ThinkPad Cpu." << endl;
        }
        void BuildMainBoard(){
            cout << "ThinkPad Main Board." << endl;
        }
    };
    
    class YogaBuilder{
    public:
        void BuildCpu(){
            cout << "Yoga Cpu." << endl;
        }
        void BuildMainBoard(){
            cout << "Yoga Main Board." << endl;
        }
    };
    
    class Director{
    public:
        void Create(IBuilder* build){
            build->BuildCpu();
            build->BuildMainboard();
        }
    };
    
    //     ****************************** 示例代码 ******************************
    //    Director *pDirecror = new Director();
    //    ThinkPadBuilder *pTPBuilder = new ThinkPadBuilder();
    //    YogaBuilder *pYogaBuilder = new YogaBuilder();
    //    组装 ThinkPad、Yoga
    //    pDirecror->Create(pTPBuilder);
    //    pDirecror->Create(pYogaBuilder);
}

/*
 ************************************************************************************************
 * 工厂方法模式
 ************************************************************************************************
 */
namespace FactoryPattern {
    class ICar{};
    class BenzCar : public ICar{};
    class AudiCar : public ICar{};
    
    class AFactory{
    public:
        virtual ICar* CreateCar() = 0;
    };
    
    class BenzFactory : public AFactory{
    public:
        ICar* CreateCar() {
            return new BenzCar();
        }
    };
    
    class AudiFactory : public AFactory{
    public:
        ICar* CreateCar() {
            return new AudiCar();
        }
    };
    
    //     ****************************** 示例代码 ******************************
    //    AFactory *pFactory = new BenzFactory();
    //    ICar *pCar = pFactory->CreateCar();
    //    pFactory = new AudiFactory();
    //    pCar = pFactory->CreateCar();
}

/*
 ************************************************************************************************
 * 适配器模式
 ************************************************************************************************
 */
namespace AdapterPattern {
    class IRussiaSocket {
    public:
        virtual void Charge() = 0;
    };
    
    class OwnCharger{
    public:
        void ChargeWithFeetFlat() {
            cout << "OwnCharger::ChargeWithFeetFlat" << endl;
        }
    };
    
    class PowerAdapter : public IRussiaSocket{
    public:
        PowerAdapter() : m_pCharger(new OwnCharger()){}
        ~PowerAdapter() {
            if(m_pCharger) delete m_pCharger;
        }
        void Charge() {
            m_pCharger->ChargeWithFeetFlat();
        }
        
    private:
        OwnCharger *m_pCharger;
    };
    
    //     ****************************** 示例代码 ******************************
    //    IRussiaSocket *pAdapter = new PowerAdapter();
    //    pAdapter->Charge();

}
#endif /* DesignModel_Create_h */

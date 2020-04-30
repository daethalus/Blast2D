#ifndef BLAST2D_LOADER_HPP
#define BLAST2D_LOADER_HPP

#include <core/logging/easylogging++.h>
#include <core/ecs/entity_manager.hpp>

//TODO
/* This is just a temporary class that I will use to try to load the content and now exactly what I need to do
 * The idea is to refactor this class to other classes and make something more generic
 *
 *
 * create binder by refection or manual?
 *
 *
 */

namespace Blast2D {

}

#define TEST_COMPONENT(T) const static bool component_##T = Blast2D::EntityManager::getInstance().createComponent<T>()

//#define MACRO_FUNC(T) const static Ref comp_##T = Blast2D::Loader::call(); \
//void test_##T(Ref ref)


namespace Blast2D {

    class Ref{
    public:
        std::string name;
    };

    class Loader {
    public:
        static void (*fun_ptr_)();

        static void load(){
            LOG(INFO) << "loading test class";
          //  (*fun_ptr_)();
            LOG(INFO) << "Called";

            auto entity = entityManager.create();
//            auto comp = entityManager.assign(entity, "WindowProperties");
//            comp.set("name", "value");

            //entityManager.create(WindowProperties{true});
            //entityManager.create(Application{true});

        }

        template<typename T>
        static bool call(T&& test) {
            return true;
         //   (*fun_ptr_)() = &test;
        }
    };

    struct Comp {
        int value;
    };


    static void test2();
    void test() {
        LOG(INFO) << "test1";
        test2();
    };
    const bool vl = Blast2D::Loader::call(&test);
    void test2() {
        LOG(INFO) << "test2";
    }



    TEST_COMPONENT(Comp);

//    MACRO_FUNC(Comp) {
//        ref.name = "aff";
//    }


}

#endif

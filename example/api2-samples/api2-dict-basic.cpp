#include <iostream>

#include "av.h"
#include "av_dictionary.h"

//using namespace std;
//using namespace av;

int main()
{
#if 0
    {
        av::Dictionary dict;
    }
#endif

#if 1
    {
        av::Dictionary dict;
        dict.set("test1", "test value");
        dict.set("test2", 31337);

		std::cout << dict.get("test1") << std::endl
			 << dict.get("test2") << std::endl;
			 //<< dict.get("test3") << std::endl;

        {
			std::shared_ptr<char> sptr;
            {
                av::Dictionary::AvStringPtr ptr;
                ptr = dict.toRawStringPtr('=', ';');
				std::cout << ptr.get() << std::endl;

                sptr = std::move(ptr);
            }

			std::cout << sptr.get() << std::endl;
        }

		std::cout << dict[1] << std::endl;
    }


    {
        av::Dictionary dict;
        dict.set("test1", "test value");
        dict.set("test2", 31337);

		std::cout << std::endl;
		std::cout << "ptr: " << (void*)dict.raw() << std::endl;
		std::cout << dict.get("test1") << std::endl
			 << dict.get("test2") << std::endl;

        av::Dictionary dict2 = dict;
        av::Dictionary dict3;
		std::cout << std::endl;
		std::cout << "ptr: " << (void*)dict.raw() << std::endl;
		std::cout << dict.get("test1") << std::endl
			 << dict.get("test2") << std::endl;
		std::cout << "ptr: " << (void*)dict2.raw() << std::endl;
		std::cout << dict2.get("test1") << std::endl
			 << dict2.get("test2") << std::endl;

        dict3 = dict;
		std::cout << std::endl;
		std::cout << "ptr: " << (void*)dict.raw() << std::endl;
		std::cout << dict.get("test1") << std::endl
			 << dict.get("test2") << std::endl;
		std::cout << "ptr: " << (void*)dict3.raw() << std::endl;
		std::cout << dict3.get("test1") << std::endl
			 << dict3.get("test2") << std::endl;

        av::Dictionary dict4 = std::move(dict2);
        av::Dictionary dict5;
		std::cout << std::endl;
		std::cout << "ptr: " << (void*)dict2.raw() << std::endl;
		std::cout << "ptr: " << (void*)dict4.raw() << std::endl;
		std::cout << dict4.get("test1") << std::endl
			 << dict4.get("test2") << std::endl;

        dict5 = std::move(dict3);
		std::cout << std::endl;
		std::cout << "ptr: " << (void*)dict3.raw() << std::endl;
		std::cout << "ptr: " << (void*)dict5.raw() << std::endl;
		std::cout << dict5.get("test1") << std::endl
			 << dict5.get("test2") << std::endl;

    }

    {
        av::Dictionary dict;
        dict.set("test1", "test value");
        dict.set("test2", 31337);
        dict.set("test3", "other value");

        for (auto const &i : dict)
        {
			std::cout << i.key() << " -> " << i.value() << std::endl;
        }

        auto it = dict.begin();
        for (int i = 0; it != dict.end(); ++it, ++i)
        {
			std::cout << (*it).key() << " -> " << (*it).value() << std::endl;
			std::cout << it->key() << " -> " << it->value() << std::endl;
			it->set(std::to_string(i));
        }

        {
			auto it1 = dict.cbegin();
			for (int i = 0; it1 != dict.cend(); ++it1, ++i)
            {
				std::cout << (*it1).key() << " -> " << (*it1).value() << std::endl;
				std::cout << it1->key() << " -> " << it1->value() << std::endl;
                //it->set(to_string(i)); // <-- compilation error
            }
        }

		std::cout << "End\n";
    }

    {
        av::Dictionary dict = {
            {"init1", "value1"},
            {"init2", "value2"}
        };

        for (auto const &i : dict)
        {
			std::cout << i.key() << " -> " << i.value() << std::endl;
        }

        dict = {
            {"init3", "value3"},
            {"init4", "value4"},
        };

        for (auto const &i : dict)
        {
			std::cout << i.key() << " -> " << i.value() << std::endl;
        }
    }


    {
        av::DictionaryArray arr = {
            {
                {"i1", "v1"},
                {"i2", "v2"}
            },
            {
                {"i3", "v3"},
                {"i4", "v4"}
            }
        };

        auto v = arr[0];
        v.set("i1", "change1");
        auto c = arr[0];
        c.set("i1", "change2");
        auto d = arr[0];

		std::cout << v.get("i1") << ", " << c.get("i1") << ", " << d.get("i1") << std::endl;

        auto& e = arr[0];
        e.set("i1", "change3");
        auto& f = arr[0];
		std::cout << e.get("i1") << ", " << f.get("i1") << std::endl;

    }

    {
		av::Dictionary dict;
		dict.parseString("key1=val1;key2=val2", "=", ";");
		dict.parseString("key3=val1;key4=val2", "=", ";");

		std::error_code ec;
		std::cout << " str: " << dict.toString(':', ',', ec) << std::endl;
		std::cout << " err: " << ec << ", " << ec.message() << std::endl;
		std::cout << " str: " << dict.toString(':', '\0', ec) << std::endl;
		std::cout << " err: " << ec << ", " << ec.message() << std::endl;

        auto raw = dict.toRawStringPtr('=', ',', ec);
		std::cout << " str: " << raw.get() << std::endl;
		std::cout << " err: " << ec << ", " << ec.message() << std::endl;

    }
#endif

#if 1
    {
#if 0
        {
            AVDictionary *rdict = nullptr;
            av_dict_set(&rdict, "rdict", "rvalue", 0);

            av::Dictionary dict = {
                {"dict", "val"}
            };

            dict.assign(rdict);
        }
#endif

#if 0
        {
            Dictionary dict;
            //dict.set("test")
            dict["test"] = "value";
            dict["test2"] = "fdsfdsfdsfdsfsdfsd";

            auto ptr  = dict.release();
            auto ptr2 = dict.rawPtr();

            //
            // simulate external api
            //
            // {
            av_freep(ptr2);
            //av_freep(dict.rawPtr());

			std::cout << (void*)dict.raw() << std::endl;

            AVDictionary *rdict = nullptr;
            av_dict_set(&rdict, "rdict", "rvalue", 0);
            *ptr2 = rdict;
            //
            // }

            dict.assign(*ptr2);

        }
#endif

    }
#endif

#if 0
    {
        DictionaryArray arr = {
            {
                {"key1", "val1"}
            },
            {
                {"key2", "val2"}
            },
        };

        auto arr2 = arr;
        auto raw = arr2.raws();

        for (size_t i = 0; i < arr2.size(); ++i)
        {
            auto ptr1 = raw[i];
            auto ptr2 = arr2[i].raw();
            auto ptr3 = arr[i].raw();

			std::cout << (void*)ptr1 << " vs " << (void*)ptr2 << " vs " << (void*)ptr3 << std::endl;
        }
    }
#endif

    return 0;
}

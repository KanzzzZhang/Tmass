// Standard archive records for single stand-alone objects and simple arrays

#ifndef GENERS_ARCHIVERECORD_HH_
#define GENERS_ARCHIVERECORD_HH_

#include <vector>

#include "geners/AbsRecord.hh"
#include "geners/ArrayAdaptor.hh"
#include "geners/IOIsAnyPtr.hh"
#include "geners/static_check.h"
#include "geners/CPP11_shared_ptr.hh"
#include "geners/GenericIO.hh"

namespace gs {
    template <typename T>
    class ArchiveRecord : public AbsRecord
    {
    public:
        ArchiveRecord(const T& object, const char* name, const char* category)
            : AbsRecord(ClassId::makeId<T>(), "gs::Single", name, category),
              obj_(object)
        {
            // Can not store pointer types explicitly -- there is no good way
            // to retrieve them
            LOKI_STATIC_CHECK((!IOIsAnyPtr<T>::value),
                              can_not_use_archive_records_with_pointers);
        }

    private:
        ArchiveRecord();

        inline virtual bool writeData(std::ostream& os) const
            {return write_item(os, obj_, true);}

        const T& obj_;
    };


    template <typename T>
    class ArchiveRecord<ArrayAdaptor<T> > : public AbsRecord
    {
    public:
        ArchiveRecord(const ArrayAdaptor<T>& arr,
                      const char* name, const char* category)
            : AbsRecord(ClassId::makeId<T>(), "gs::Array", name, category),
              obj_(arr) {}

    private:
        ArchiveRecord();

        inline virtual bool writeData(std::ostream& os) const
            {return write_array(os, obj_.begin(), obj_.size());}

        ArrayAdaptor<T> obj_;
    };


    // The following record makes a copy of the object instead of just
    // storing a reference to it. Naturally, the template parameter type
    // must have a copy constructor.
    template <typename T>
    class ArchiveValueRecord : public AbsRecord
    {
    public:
        ArchiveValueRecord(const T& object,
                           const char* name, const char* category)
            : AbsRecord(ClassId::makeId<T>(), "gs::Single", name, category),
              obj_(new T(object))
        {
            // Can not store pointer types explicitly -- there is no good way
            // to retrieve them
            LOKI_STATIC_CHECK((!IOIsAnyPtr<T>::value),
                              can_not_use_archive_records_with_pointers);
        }

    private:
        ArchiveValueRecord();

        inline virtual bool writeData(std::ostream& os) const
            {return write_item(os, *obj_, true);}

        CPP11_shared_ptr<T> obj_;
    };


    template <typename T>
    class ArchiveValueRecord<ArrayAdaptor<T> > : public AbsRecord
    {
    public:
        ArchiveValueRecord(const ArrayAdaptor<T>& arr,
                           const char* name, const char* category)
            : AbsRecord(ClassId::makeId<T>(), "gs::Array", name, category),
              obj_(new std::vector<T>(arr.begin(), arr.end())) {}

    private:
        ArchiveValueRecord();

        inline virtual bool writeData(std::ostream& os) const
            {return write_array(os, obj_->begin(), obj_->size());}

        CPP11_shared_ptr<std::vector<T> > obj_;
    };
}

#endif // GENERS_ARCHIVERECORD_HH_

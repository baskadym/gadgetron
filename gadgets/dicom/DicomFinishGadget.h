#ifndef DICOMFINISHGADGET_H
#define DICOMFINISHGADGET_H

#include "gadgetrondicom_export.h"
#include "Gadget.h"
#include "hoNDArray.h"
#include "GadgetMRIHeaders.h"
#include "ismrmrd.h"
#include "GadgetStreamController.h"

#include <string>
#include <map>
#include <complex>


namespace Gadgetron {

template <typename T>
class EXPORTGADGETSDICOM DicomFinishGadget :
    public Gadget2<ISMRMRD::ImageHeader, hoNDArray< T > >
{
    public:
        DicomFinishGadget<T>()
            : Gadget2<ISMRMRD::ImageHeader, hoNDArray<T> >()
            , dcmFile()
            , seriesIUIDRoot()
        { }

    protected:
        virtual int process_config(ACE_Message_Block * mb);
        virtual int process(GadgetContainerMessage<ISMRMRD::ImageHeader>* m1,
                GadgetContainerMessage< hoNDArray< T > >* m2);

    private:
        DcmFileFormat dcmFile;
        std::string seriesIUIDRoot;
        long initialSeriesNumber;
        std::map <unsigned int, std::string> seriesIUIDs;
};

class EXPORTGADGETSDICOM DicomFinishGadgetUSHORT :
    public DicomFinishGadget<ACE_UINT16>
{
    public:
        GADGET_DECLARE(DicomFinishGadgetUSHORT);
};

class EXPORTGADGETSDICOM DicomFinishGadgetFLOAT :
    public DicomFinishGadget<float>
{
    public:
        GADGET_DECLARE(DicomFinishGadgetFLOAT);
};

/*
class EXPORTGADGETSDICOM DicomFinishGadgetCPLX :
    public DicomFinishGadget< std::complex<float> >
{
    public:
        GADGET_DECLARE(DicomFinishGadgetCPLX);
};
*/

} /* namespace Gadgetron */

#endif //DICOMFINISHGADGET_H

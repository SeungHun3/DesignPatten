#include "02_Builder.h"

PersonBuilder Person::create()
{
	return PersonBuilder{};
}

PersonAddressBuilder PersonBuilderBase::lives() const
{
	return PersonAddressBuilder{ person };
}

PersonJobBuilder PersonBuilderBase::works() const
{
	return PersonJobBuilder{ person };
}

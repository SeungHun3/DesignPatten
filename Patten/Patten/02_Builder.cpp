#include "02_Builder.h"

PersonAddressBuilder PersonBuilderBase::lives() const
{
	return PersonAddressBuilder{ person };
}

PersonJobBuilder PersonBuilderBase::works() const
{
	return PersonJobBuilder{ person };
}

PersonBuilder Person::create()
{
	return PersonBuilder{};
}
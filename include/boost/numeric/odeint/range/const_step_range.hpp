/*
  [auto_generated]
  boost/numeric/odeint/range/const_step_range.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_RANGE_CONST_STEP_RANGE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_RANGE_CONST_STEP_RANGE_HPP_INCLUDED

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/iterator/iterator_facade.hpp>




namespace boost {
namespace numeric {
namespace odeint {
    
    
template< typename Stepper , typename State , typename System , typename Time >
class const_step_range
{
public:

    typedef Stepper stepper_type;
    typedef typename boost::numeric::odeint::unwrap_reference< stepper_type >::type unwrapped_stepper_type;
    typedef State state_type;
    typedef System system_type;
    typedef typename boost::numeric::odeint::unwrap_reference< system_type >::type unwrapped_system_type;
    typedef Time time_type;
    typedef const_step_range< stepper_type , state_type , system_type , time_type > range_type;
    
    struct const_step_iterator :
    public boost::iterator_facade
    <
        const_step_iterator ,
        state_type const ,
        boost::single_pass_traversal_tag
    >
    {
        friend class boost::iterator_core_access;
        
        const_step_iterator( range_type const* range )
        : m_range( range )
        { };
        
        
        void increment( void )
        {
            unwrapped_stepper_type &stepper = m_range->m_stepper;
            if( detail::less_eq_with_sign( static_cast< time_type >( m_range->m_current_time + m_range->m_dt ) ,
                                           m_range->m_end_time , m_range->m_dt ) )
            {
                stepper.do_step( m_range->m_system , *( m_range->m_x ) , m_range->m_current_time , m_range->m_dt );
                m_range->m_current_time += m_range->m_dt;
            } 
            else
            {
                m_range = nullptr;
            }
        }

        bool equal( const_step_iterator const& other) const
        {
            return ( m_range == other.m_range );
        }
        
        const state_type& dereference( void ) const
        {
            return *( m_range->m_x );
        }
        
        range_type const* m_range;
    };
    
    typedef const_step_iterator iterator;
    typedef const_step_iterator const_iterator;
    
    const_step_range( stepper_type stepper , state_type &x , system_type system , time_type start_time , time_type end_time , time_type dt )
    : m_stepper( stepper )
    , m_x( &x )
    , m_system( system )
    , m_current_time( start_time ) , m_end_time( end_time ) , m_dt( dt )
    { }
    
    iterator begin( void )
    {
        return iterator( this );
    }

    iterator end( void )
    {
        return iterator( nullptr );
    }
    
    const_iterator begin( void ) const
    {
        return const_iterator( this );
    }
    
    const_iterator end( void ) const
    {
        return const_iterator( nullptr );
    }
    
    
    
    
    
private:

    mutable stepper_type m_stepper;
    state_type *m_x;
    mutable system_type m_system;
    mutable time_type m_current_time;
    time_type m_end_time;
    time_type m_dt;
};

template< typename Stepper , typename State , typename System , typename Time >
const_step_range< Stepper , State , System , Time >
make_const_step_range( Stepper stepper , State &x , System system , Time start_time , Time end_time , Time dt )
{
    return const_step_range< Stepper , State , System , Time >( stepper , x , system , start_time , end_time , dt );
}




} // namespace odeint
} // namespace numeric
} // namespace boost

/*
namespace boost {

    
template< typename Stepper , typename State , typename System , typename Time >
struct range_mutable_iterator< boost::numeric::odeint::const_step_range< Stepper , State , System , Time > >
{
    typedef boost::numeric::odeint::const_step_range< Stepper , State , System , Time > range_type;
    typedef typename range_type::const_step_iterator type;
};

template< typename Stepper , typename State , typename System , typename Time >
struct range_const_iterator< boost::numeric::odeint::const_step_range< Stepper , State , System , Time > >
{
    typedef boost::numeric::odeint::const_step_range< Stepper , State , System , Time > range_type;
    typedef typename range_type::const_step_iterator type;
};


} // namespace boost
*/



/*
namespace boost {
namespace numeric {
namespace odeint {
    
template< typename Stepper , typename State , typename System , typename Time >
inline typename const_step_range< Stepper , State , System , Time >::const_step_iterator
range_begin( const_step_range< Stepper , State , System , Time >& x )
{
    typedef boost::numeric::odeint::const_step_range< Stepper , State , System , Time > range_type;
    typedef typename range_type::const_step_iterator iterator;
    return iterator( x , false );
}

template< typename Stepper , typename State , typename System , typename Time >
inline typename const_step_range< Stepper , State , System , Time >::const_step_iterator
range_begin( const_step_range< Stepper , State , System , Time > const& x )
{
    typedef boost::numeric::odeint::const_step_range< Stepper , State , System , Time > range_type;
    typedef typename range_type::const_step_iterator iterator;
    return iterator( x , false );
}

template< typename Stepper , typename State , typename System , typename Time >
inline typename const_step_range< Stepper , State , System , Time >::const_step_iterator
range_end( const_step_range< Stepper , State , System , Time >& x )
{
    typedef boost::numeric::odeint::const_step_range< Stepper , State , System , Time > range_type;
    typedef typename range_type::const_step_iterator iterator;
    return iterator( x , true );
}

template< typename Stepper , typename State , typename System , typename Time >
inline typename const_step_range< Stepper , State , System , Time >::const_step_iterator
range_end( const_step_range< Stepper , State , System , Time > const& x )
{
    typedef boost::numeric::odeint::const_step_range< Stepper , State , System , Time > range_type;
    typedef typename range_type::const_step_iterator iterator;
    return iterator( x , false );
}


} // namespace odeint
} // namespace numeric
} // namespace boost*/


#endif // BOOST_NUMERIC_ODEINT_RANGE_CONST_STEP_RANGE_HPP_INCLUDED
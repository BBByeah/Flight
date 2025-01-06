# flight_system.py

from dataclasses import dataclass
from typing import List, Dict , Callable
from datetime import datetime
import csv
import os

from enum import Enum  


class QueryType(Enum):
    BY_TIME = 1      
    BY_SITE = 2      
    BY_PRICE = 3     
    BY_SEATS = 4     
    RETURN_MENU = 5  

# Data Structure Definitions
@dataclass
class Site:
    site_code: int
    longitude: float
    latitude: float
    site_name: str
    related_route_codes: List[int]


@dataclass
class Route:
    route_code: int
    related_sites: List[int]  # [start_site, end_site]
    distance: float
    prices: List[float]  # [first_class, business_class, economy_class]
    duration: int  # in seconds


@dataclass
class Flight:
    flight_code: int
    start_site_code: int
    end_site_code: int
    departure_time: datetime
    landing_time: datetime
    remaining_tickets: List[int]  # [first_class, business_class, economy_class]
    total_prices: List[float]
    total_duration: int  # in seconds


@dataclass
class Ticket:
    ticket_code: int
    flight_code: int
    customer_id: int
    customer_name: str
    seat_type: str
    bought_time: datetime


# System Class Definitions
class SiteSystem:
    def __init__(self):
        self.sites: List[Site] = []

    def add_site(self):
        """Add a site"""
        try:
            print("\n=== Add Site ===")
            site_code = int(input("Enter site code: "))
            longitude = float(input("Enter longitude: "))
            latitude = float(input("Enter latitude: "))
            site_name = input("Enter site name: ")
            related_routes = input("Enter related route codes (comma separated): ").split(',')
            related_route_codes = [int(code) for code in related_routes if code]

            new_site = Site(
                site_code=site_code,
                longitude=longitude,
                latitude=latitude,
                site_name=site_name,
                related_route_codes=related_route_codes
            )
            self.sites.append(new_site)
            print("Site added successfully!")
            return True
        except ValueError as e:
            print(f"Input error: {e}")
            return False

    def delete_site(self):
        """Delete a site"""
        try:
            site_code = int(input("Enter site code to delete: "))
            for i, site in enumerate(self.sites):
                if site.site_code == site_code:
                    del self.sites[i]
                    print("Site deleted successfully!")
                    return True
            print("Site not found!")
            return False
        except ValueError as e:
            print(f"Input error: {e}")
            return False

    def sort_sites(self):
        """Site sorting functionality"""
        while True:
            print("\n=== Sort Sites ===")
            print("1. Sort by site code")
            print("2. Sort by site name") 
            print("3. Sort by longitude")
            print("4. Sort by latitude")
            print("5. Sort by number of related routes")
            print("6. Return to previous menu")

            try:
                choice = int(input("Please select sorting method (1-6): "))
                
                sort_methods = {
                    1: ("Site Code", lambda x: x.site_code),
                    2: ("Site Name", lambda x: x.site_name),
                    3: ("Longitude", lambda x: x.longitude),
                    4: ("Latitude", lambda x: x.latitude),
                    5: ("Related Routes Count", lambda x: len(x.related_route_codes))
                }

                if choice in sort_methods:
                    name, key_func = sort_methods[choice]
                    self._sort_and_display(key_func, name)
                elif choice == 6:
                    break
                else:
                    print("Invalid choice!")

            except ValueError:
                print("Please enter a valid number!")
            except Exception as e:
                print(f"An error occurred: {e}")

    def _sort_and_display(self, key_func: Callable, sort_name: str):
        """Execute sorting and display results"""
        try:
            # Ask for sort direction
            print("\nSort direction:")
            print("1. Ascending")
            print("2. Descending")
            direction = int(input("Please select sort direction (1-2): "))

            # Execute sorting
            reverse = direction == 2
            self.sites.sort(key=key_func, reverse=reverse)

            # Display sorting results
            print(f"\n=== Results sorted by {sort_name} ({'Descending' if reverse else 'Ascending'}) ===")
            self.show_site_list()

        except ValueError:
            print("Please enter a valid number!")
        except Exception as e:
            print(f"Error occurred during sorting: {e}")

    def show_site_list(self):
        """Display site list"""
        if not self.sites:
            print("No site data available!")
            return

        # Calculate maximum width for each column
        max_code_width = max(len(str(site.site_code)) for site in self.sites)
        max_name_width = max(len(site.site_name) for site in self.sites)
        max_routes_width = max(len(','.join(map(str, site.related_route_codes))) for site in self.sites)

        # Set minimum widths
        max_code_width = max(max_code_width, 8)
        max_name_width = max(max_name_width, 12)
        max_routes_width = max(max_routes_width, 15)

        # Print header
        print("\n" + "=" * (max_code_width + max_name_width + 32 + max_routes_width))
        print(f"{'Site Code':<{max_code_width}} "
              f"{'Site Name':<{max_name_width}} "
              f"{'Longitude':>10} "
              f"{'Latitude':>10} "
              f"{'Related Routes':<{max_routes_width}}")
        print("-" * (max_code_width + max_name_width + 32 + max_routes_width))

        # Print data
        for site in self.sites:
            routes = ','.join(map(str, site.related_route_codes))
            print(f"{site.site_code:<{max_code_width}} "
                  f"{site.site_name:<{max_name_width}} "
                  f"{site.longitude:>10.2f} "
                  f"{site.latitude:>10.2f} "
                  f"{routes:<{max_routes_width}}")
        
        print("=" * (max_code_width + max_name_width + 32 + max_routes_width))
        print(f"Total: {len(self.sites)} sites")

        
class RouteSystem:
    def __init__(self):
        self.routes: List[Route] = []
        self.sites = []  # 添加sites属性

    def add_route(self):
        """Add a route"""
        try:
            print("\n=== Add Route ===")
            route_code = int(input("Enter route code: "))
            start_site = int(input("Enter start site code: "))
            end_site = int(input("Enter end site code: "))
            distance = float(input("Enter distance (km): "))
            prices = [
                float(input("Enter first class price: ")),
                float(input("Enter business class price: ")),
                float(input("Enter economy class price: "))
            ]
            duration = int(input("Enter flight duration (minutes): ")) * 60

            new_route = Route(
                route_code=route_code,
                related_sites=[start_site, end_site],
                distance=distance,
                prices=prices,
                duration=duration
            )
            self.routes.append(new_route)
            print("Route added successfully!")
            return True
        except ValueError as e:
            print(f"Input error: {e}")
            return False

    def delete_route(self):
        """Delete a route"""
        try:
            print("\n=== Delete Route ===")
            self.show_route_list()
            if not self.routes:
                return False
                
            route_code = int(input("Enter route code to delete: "))
            for i, route in enumerate(self.routes):
                if route.route_code == route_code:
                    del self.routes[i]
                    print("Route deleted successfully!")
                    return True
            print("Route not found!")
            return False
        except ValueError as e:
            print(f"Input error: {e}")
            return False

    def modify_route(self):
        """Modify a route"""
        try:
            print("\n=== Modify Route ===")
            self.show_route_list()
            if not self.routes:
                return False

            route_code = int(input("Enter route code to modify: "))
            for route in self.routes:
                if route.route_code == route_code:
                    print("\nEnter new values (press Enter to keep current value):")
                    
                    # Get new start site
                    new_start = input(f"Start site code [{route.related_sites[0]}]: ")
                    if new_start:
                        route.related_sites[0] = int(new_start)

                    # Get new end site  
                    new_end = input(f"End site code [{route.related_sites[1]}]: ")
                    if new_end:
                        route.related_sites[1] = int(new_end)

                    # Get new distance
                    new_distance = input(f"Distance in km [{route.distance}]: ")
                    if new_distance:
                        route.distance = float(new_distance)

                    # Get new prices
                    new_first = input(f"First class price [{route.prices[0]}]: ")
                    if new_first:
                        route.prices[0] = float(new_first)
                        
                    new_business = input(f"Business class price [{route.prices[1]}]: ")
                    if new_business:
                        route.prices[1] = float(new_business)
                        
                    new_economy = input(f"Economy class price [{route.prices[2]}]: ")
                    if new_economy:
                        route.prices[2] = float(new_economy)

                    # Get new duration
                    new_duration = input(f"Duration in minutes [{route.duration/60}]: ")
                    if new_duration:
                        route.duration = int(new_duration) * 60

                    print("Route modified successfully!")
                    return True
                    
            print("Route not found!")
            return False
        except ValueError as e:
            print(f"Input error: {e}")
            return False

    def sort_routes(self):
        """Route sorting functionality"""
        while True:
            print("\n=== Sort Routes ===")
            print("1. Sort by route code")
            print("2. Sort by distance")
            print("3. Sort by duration")
            print("4. Sort by first class price")
            print("5. Sort by business class price") 
            print("6. Sort by economy class price")
            print("7. Return to previous menu")

            try:
                choice = int(input("Please select sorting method (1-7): "))
                
                sort_methods = {
                    1: ("Route Code", lambda x: x.route_code),
                    2: ("Distance", lambda x: x.distance),
                    3: ("Duration", lambda x: x.duration),
                    4: ("First Class Price", lambda x: x.prices[0]),
                    5: ("Business Class Price", lambda x: x.prices[1]),
                    6: ("Economy Class Price", lambda x: x.prices[2])
                }

                if choice in sort_methods:
                    name, key_func = sort_methods[choice]
                    self._sort_and_display(key_func, name)
                elif choice == 7:
                    break
                else:
                    print("Invalid choice!")

            except ValueError:
                print("Please enter a valid number!")
            except Exception as e:
                print(f"An error occurred: {e}")

    def _sort_and_display(self, key_func: Callable, sort_name: str):
        """Execute sorting and display results"""
        try:
            print("\nSort direction:")
            print("1. Ascending")
            print("2. Descending")
            direction = int(input("Please select sort direction (1-2): "))

            reverse = direction == 2
            self.routes.sort(key=key_func, reverse=reverse)

            print(f"\n=== Results sorted by {sort_name} ({'Descending' if reverse else 'Ascending'}) ===")
            self.show_route_list()

        except ValueError:
            print("Please enter a valid number!")
        except Exception as e:
            print(f"Error occurred during sorting: {e}")

    def show_route_list(self):
        """Display route list"""
        if not self.routes:
            print("No route data available!")
            return

        # Get site_system instance to display site names
        site_system = None
        if hasattr(self, 'site_system'):
            site_system = self.site_system
        
        if not site_system or not site_system.sites:
            # If no site system data, show basic info only
            print("\n=== Route List (Site names not available) ===")
            print(f"{'Code':<8}{'Start':<10}{'End':<10}{'Distance(km)':<12}{'Duration(h)':<8}{'Prices($)'}")
            print("-" * 60)
            for route in self.routes:
                duration_hours = route.duration / 3600
                prices = '/'.join(map(str, route.prices))
                
                print(f"{route.route_code:<8}{route.related_sites[0]:<10}"
                      f"{route.related_sites[1]:<10}{route.distance:<12.1f}"
                      f"{duration_hours:<8.1f}{prices}")
            return

        # Show full information when site data is available
        print("\n=== Route List ===")
        print(f"{'Code':<8}{'Start Site':<25}{'End Site':<25}{'Distance(km)':<12}{'Duration(h)':<8}{'Prices($)'}")
        print("-" * 90)
        for route in self.routes:
            # Get site name mapping
            site_names = {}
            for site in site_system.sites:
                if site.site_code in route.related_sites:
                    site_names[site.site_code] = site.site_name

            duration_hours = route.duration / 3600
            prices = '/'.join(map(str, route.prices))
            
            # Get start site name
            start_site_code = route.related_sites[0]
            start_site_name = site_names.get(start_site_code, 'Unknown')
            start_site = f"{start_site_code} - {start_site_name}"
            
            # Get end site name
            end_site_code = route.related_sites[1]
            end_site_name = site_names.get(end_site_code, 'Unknown')
            end_site = f"{end_site_code} - {end_site_name}"
            
            print(f"{route.route_code:<8}{start_site:<25}"
                  f"{end_site:<25}{route.distance:<12.1f}"
                  f"{duration_hours:<8.1f}{prices}")
class FlightSystem:
    def __init__(self):
        self.flights: List[Flight] = []
        self.routes = []  # Add routes attribute

    def add_flight(self):
        """Add a flight"""
        try:
            print("\n=== Add Flight ===")
            flight_code = int(input("Enter flight code: "))
            start_site = int(input("Enter start site code: "))
            end_site = int(input("Enter end site code: "))
            
            # Get departure time
            departure_str = input("Enter departure time (YYYY-MM-DD HH:MM): ")
            departure_time = datetime.strptime(departure_str, "%Y-%m-%d %H:%M")
            
            # Get landing time
            landing_str = input("Enter landing time (YYYY-MM-DD HH:MM): ")
            landing_time = datetime.strptime(landing_str, "%Y-%m-%d %H:%M")
            
            # Get remaining tickets for each class
            remaining = [
                int(input("Enter remaining first class tickets: ")),
                int(input("Enter remaining business class tickets: ")),
                int(input("Enter remaining economy class tickets: "))
            ]
            
            # Get prices for each class
            prices = [
                float(input("Enter first class price: ")),
                float(input("Enter business class price: ")),
                float(input("Enter economy class price: "))
            ]
            
            # Calculate total duration in seconds
            duration = int((landing_time - departure_time).total_seconds())

            new_flight = Flight(
                flight_code=flight_code,
                start_site_code=start_site,
                end_site_code=end_site,
                departure_time=departure_time,
                landing_time=landing_time,
                remaining_tickets=remaining,
                total_prices=prices,
                total_duration=duration
            )
            self.flights.append(new_flight)
            print("Flight added successfully!")
            return True
        except ValueError as e:
            print(f"Input error: {e}")
            return False

    def delete_flight(self):
        """Delete a flight"""
        try:
            print("\n=== Delete Flight ===")
            self.show_flight_list()
            if not self.flights:
                return False
                
            flight_code = int(input("Enter flight code to delete: "))
            for i, flight in enumerate(self.flights):
                if flight.flight_code == flight_code:
                    del self.flights[i]
                    print("Flight deleted successfully!")
                    return True
            print("Flight not found!")
            return False
        except ValueError as e:
            print(f"Input error: {e}")
            return False

    def modify_flight(self):
        """Modify a flight"""
        try:
            print("\n=== Modify Flight ===")
            self.show_flight_list()
            if not self.flights:
                return False

            flight_code = int(input("Enter flight code to modify: "))
            for flight in self.flights:
                if flight.flight_code == flight_code:
                    print("\nEnter new values (press Enter to keep current value):")
                    
                    # Get new start site
                    new_start = input(f"Start site code [{flight.start_site_code}]: ")
                    if new_start:
                        flight.start_site_code = int(new_start)

                    # Get new end site
                    new_end = input(f"End site code [{flight.end_site_code}]: ")
                    if new_end:
                        flight.end_site_code = int(new_end)

                    # Get new departure time
                    current_departure = flight.departure_time.strftime("%Y-%m-%d %H:%M")
                    new_departure = input(f"Departure time [{current_departure}]: ")
                    if new_departure:
                        flight.departure_time = datetime.strptime(new_departure, "%Y-%m-%d %H:%M")

                    # Get new landing time
                    current_landing = flight.landing_time.strftime("%Y-%m-%d %H:%M")
                    new_landing = input(f"Landing time [{current_landing}]: ")
                    if new_landing:
                        flight.landing_time = datetime.strptime(new_landing, "%Y-%m-%d %H:%M")
                        flight.total_duration = int((flight.landing_time - flight.departure_time).total_seconds())

                    # Get new remaining tickets
                    for i, ticket_type in enumerate(['first', 'business', 'economy']):
                        new_remaining = input(f"Remaining {ticket_type} class tickets [{flight.remaining_tickets[i]}]: ")
                        if new_remaining:
                            flight.remaining_tickets[i] = int(new_remaining)

                    # Get new prices
                    for i, ticket_type in enumerate(['first', 'business', 'economy']):
                        new_price = input(f"{ticket_type.capitalize()} class price [{flight.total_prices[i]}]: ")
                        if new_price:
                            flight.total_prices[i] = float(new_price)

                    print("Flight modified successfully!")
                    return True
                    
            print("Flight not found!")
            return False
        except ValueError as e:
            print(f"Input error: {e}")
            return False

    def sort_flights(self):
        """Flight sorting functionality"""
        while True:
            print("\n=== Sort Flights ===")
            print("1. Sort by flight code")
            print("2. Sort by departure time") 
            print("3. Sort by duration")
            print("4. Sort by first class price")
            print("5. Sort by business class price")
            print("6. Sort by economy class price")
            print("7. Sort by remaining first class tickets")
            print("8. Sort by remaining business class tickets") 
            print("9. Sort by remaining economy class tickets")
            print("10. Return to previous menu")

            try:
                choice = int(input("Please select sorting method (1-10): "))
                
                sort_methods = {
                    1: ("Flight Code", lambda x: x.flight_code),
                    2: ("Departure Time", lambda x: x.departure_time),
                    3: ("Duration", lambda x: x.total_duration),
                    4: ("First Class Price", lambda x: x.total_prices[0]),
                    5: ("Business Class Price", lambda x: x.total_prices[1]),
                    6: ("Economy Class Price", lambda x: x.total_prices[2]),
                    7: ("Remaining First Class", lambda x: x.remaining_tickets[0]),
                    8: ("Remaining Business Class", lambda x: x.remaining_tickets[1]),
                    9: ("Remaining Economy Class", lambda x: x.remaining_tickets[2])
                }

                if choice in sort_methods:
                    name, key_func = sort_methods[choice]
                    self._sort_and_display(key_func, name)
                elif choice == 10:
                    break
                else:
                    print("Invalid choice!")

            except ValueError:
                print("Please enter a valid number!")
            except Exception as e:
                print(f"An error occurred: {e}")

    def _sort_and_display(self, key_func: Callable, sort_name: str):
        """Execute sorting and display results"""
        try:
            print("\nSort direction:")
            print("1. Ascending")
            print("2. Descending")
            direction = int(input("Please select sort direction (1-2): "))

            reverse = direction == 2
            self.flights.sort(key=key_func, reverse=reverse)

            print(f"\n=== Results sorted by {sort_name} ({'Descending' if reverse else 'Ascending'}) ===")
            self.show_flight_list()

        except ValueError:
            print("Please enter a valid number!")
        except Exception as e:
            print(f"Error occurred during sorting: {e}")

    def show_flight_list(self):
        """Display flight list"""
        if not self.flights:
            print("No flight data available!")
            return

        print("\n=== Flight List ===")
        print(f"{'Code':<8}{'Start':<8}{'End':<8}{'Departure':<20}"
              f"{'Landing':<20}{'Duration(h)':<12}{'Remaining(First/Business/Economy)':<30}{'Prices($)'}")
        print("-" * 112)
        
        for flight in self.flights:
            # Add class labels to remaining tickets
            remaining = f"{flight.remaining_tickets[0]}F/{flight.remaining_tickets[1]}B/{flight.remaining_tickets[2]}E"
            
            # Add $ symbol to prices
            prices_with_units = [f"${x}" for x in flight.total_prices]
            prices = '/'.join(prices_with_units)
            
            departure = flight.departure_time.strftime("%Y-%m-%d %H:%M")
            landing = flight.landing_time.strftime("%Y-%m-%d %H:%M")
            
            # Calculate duration in hours
            duration_hours = flight.total_duration / 3600
            
            print(f"{flight.flight_code:<8}{flight.start_site_code:<8}"
                  f"{flight.end_site_code:<8}{departure:<20}{landing:<20}"
                  f"{duration_hours:<12.1f}{remaining:<30}{prices}")
class TicketingSystem:
    def __init__(self):
        self.tickets: List[Ticket] = []
        self.query_flight: Flight = None  # Corresponds to queryFlight member in C++
        
    def query_flight(self, query_type: QueryType) -> Flight:
        """
        Query flight based on query type
        Args:
            query_type: Type of query
        Returns:
            Flight: The queried flight object
        """
        try:
            if query_type == QueryType.BY_CODE:
                flight_code = input("Enter flight code: ")
                for flight in self.flight_system.flights:
                    if flight.flight_code == flight_code:
                        return flight
                        
            elif query_type == QueryType.BY_ROUTE:
                start = input("Enter departure site code: ")
                end = input("Enter arrival site code: ")
                for flight in self.flight_system.flights:
                    if flight.start_site_code == start and flight.end_site_code == end:
                        return flight
                        
            elif query_type == QueryType.BY_TIME:
                date_str = input("Enter date (YYYY-MM-DD): ")
                date = datetime.strptime(date_str, "%Y-%m-%d").date()
                for flight in self.flight_system.flights:
                    if flight.departure_time.date() == date:
                        return flight
                        
            print("No matching flight found!")
            return None
            
        except Exception as e:
            print(f"Error querying flight: {e}")
            return None
        
    def add_ticket(self):
        """
        Add a new ticket
        """
        try:
            # Query the flight first
            flight = self.query_flight(QueryType.BY_CODE)
            if not flight:
                return
                
            # Get customer details
            customer_name = input("Enter customer name: ")
            print("\nSelect ticket class:")
            print("1. First Class")
            print("2. Business Class") 
            print("3. Economy Class")
            
            class_choice = int(input("Enter choice (1-3): "))
            if not 1 <= class_choice <= 3:
                print("Invalid class choice!")
                return
                
            # Check seat availability
            if flight.remaining_tickets[class_choice-1] <= 0:
                print("No seats available in selected class!")
                return
                
            # Create and add ticket
            ticket = Ticket(
                customer_name=customer_name,
                flight_code=flight.flight_code,
                seat_type=class_choice,
                price=flight.total_prices[class_choice-1]
            )
            
            self.tickets.append(ticket)
            flight.remaining_tickets[class_choice-1] -= 1
            
            print("Ticket booked successfully!")
            
        except ValueError:
            print("Invalid input!")
        except Exception as e:
            print(f"Error adding ticket: {e}")

    def show_ticket_list(self):
        """Display ticket list"""
        if not self.tickets:
            print("No tickets available!")
            return

        print("\n=== Ticket List ===")
        print(f"{'Flight Code':<12}{'Customer Name':<20}{'Class':<15}{'Price($)':<10}")
        print("-" * 57)

        class_names = {1: "First Class", 2: "Business Class", 3: "Economy Class"}
        
        for ticket in self.tickets:
            print(f"{ticket.flight_code:<12}"
                  f"{ticket.customer_name:<20}"
                  f"{class_names[ticket.seat_type]:<15}"
                  f"${ticket.price:<10.2f}")


class DataSystem:
    def __init__(self, site_system: SiteSystem, route_system: RouteSystem,
                 flight_system: FlightSystem, ticketing_system: TicketingSystem):
        self.site_system = site_system
        self.route_system = route_system
        self.flight_system = flight_system
        self.ticketing_system = ticketing_system

    def save_data(self):
        """Save data to CSV files"""
        try:
            # Save site data
            with open('sites.csv', 'w', newline='', encoding='utf-8') as f:
                writer = csv.writer(f)
                writer.writerow(['SiteCode', 'Longitude', 'Latitude', 'SiteName', 'RelatedRoutes'])
                for site in self.site_system.sites:
                    writer.writerow([
                        site.site_code, site.longitude, site.latitude,
                        site.site_name, ';'.join(map(str, site.related_route_codes))
                    ])

            # Save route data  
            with open('routes.csv', 'w', newline='', encoding='utf-8') as f:
                writer = csv.writer(f)
                writer.writerow(['RouteCode', 'StartSite', 'EndSite', 'Distance',
                                 'FirstClass', 'BusinessClass', 'EconomyClass', 'Duration'])
                for route in self.route_system.routes:
                    writer.writerow([
                        route.route_code, route.related_sites[0], route.related_sites[1],
                        route.distance, *route.prices, route.duration
                    ])

            # Save flight data
            with open('flights.csv', 'w', newline='', encoding='utf-8') as f:
                writer = csv.writer(f)
                writer.writerow(['FlightCode', 'StartSite', 'EndSite', 'DepartureTime', 'LandingTime',
                               'FirstRemaining', 'BusinessRemaining', 'EconomyRemaining',
                               'FirstPrice', 'BusinessPrice', 'EconomyPrice', 'Duration'])
                for flight in self.flight_system.flights:
                    writer.writerow([
                        flight.flight_code, flight.start_site_code, flight.end_site_code,
                        flight.departure_time.strftime("%Y-%m-%d %H:%M"),
                        flight.landing_time.strftime("%Y-%m-%d %H:%M"),
                        *flight.remaining_tickets, *flight.total_prices, flight.total_duration
                    ])

            # Save ticket data
            with open('tickets.csv', 'w', newline='', encoding='utf-8') as f:
                writer = csv.writer(f)
                writer.writerow(['TicketCode', 'FlightCode', 'CustomerID', 'CustomerName', 'SeatType', 'BoughtTime'])
                for ticket in self.ticketing_system.tickets:
                    writer.writerow([
                        ticket.ticket_code, ticket.flight_code, ticket.customer_id,
                        ticket.customer_name, ticket.seat_type,
                        ticket.bought_time.strftime("%Y-%m-%d %H:%M")
                    ])

            print("Data saved successfully!")
            return True
        except Exception as e:
            print(f"Error saving data: {e}")
            return False

    def load_data(self):
        """Load data from CSV files"""
        try:
            # Clear existing data
            self.site_system.sites.clear()
            self.route_system.routes.clear() 
            self.flight_system.flights.clear()
            self.ticketing_system.tickets.clear()

            # Load site data
            if os.path.exists('sites.csv'):
                with open('sites.csv', 'r', encoding='utf-8') as f:
                    reader = csv.DictReader(f)
                    for row in reader:
                        related_routes = [int(x) for x in row['RelatedRoutes'].split(';') if x]
                        site = Site(
                            site_code=int(row['SiteCode']),
                            longitude=float(row['Longitude']),
                            latitude=float(row['Latitude']),
                            site_name=row['SiteName'],
                            related_route_codes=related_routes
                        )
                        self.site_system.sites.append(site)

            # Load route data
            if os.path.exists('routes.csv'):
                with open('routes.csv', 'r', encoding='utf-8') as f:
                    reader = csv.DictReader(f)
                    for row in reader:
                        route = Route(
                            route_code=int(row['RouteCode']),
                            related_sites=[int(row['StartSite']), int(row['EndSite'])],
                            distance=float(row['Distance']),
                            prices=[float(row['FirstClass']), float(row['BusinessClass']),
                                    float(row['EconomyClass'])],
                            duration=int(row['Duration'])
                        )
                        self.route_system.routes.append(route)

            # Load flight data
            if os.path.exists('flights.csv'):
                with open('flights.csv', 'r', encoding='utf-8') as f:
                    reader = csv.DictReader(f)
                    for row in reader:
                        try:
                            # Try parsing with format YYYY/M/D H:MM first
                            try:
                                departure_time = datetime.strptime(row['DepartureTime'], "%Y/%m/%d %H:%M")
                                landing_time = datetime.strptime(row['LandingTime'], "%Y/%m/%d %H:%M")
                            except ValueError:
                                # If that fails, try the original format YYYY-MM-DD HH:MM
                                departure_time = datetime.strptime(row['DepartureTime'], "%Y-%m-%d %H:%M")
                                landing_time = datetime.strptime(row['LandingTime'], "%Y-%m-%d %H:%M")
                                
                            flight = Flight(
                                flight_code=int(row['FlightCode']),
                                start_site_code=int(row['StartSite']),
                                end_site_code=int(row['EndSite']),
                                departure_time=departure_time,
                                landing_time=landing_time,
                                remaining_tickets=[int(row['FirstRemaining']), 
                                                int(row['BusinessRemaining']),
                                                int(row['EconomyRemaining'])],
                                total_prices=[float(row['FirstPrice']),
                                            float(row['BusinessPrice']),
                                            float(row['EconomyPrice'])],
                                total_duration=int(row['Duration'])
                            )
                            self.flight_system.flights.append(flight)
                        except Exception as e:
                            print(f"Error loading flight data row: {row}")
                            print(f"Error details: {e}")
                            continue

            # Load ticket data
            if os.path.exists('tickets.csv'):
                with open('tickets.csv', 'r', encoding='utf-8') as f:
                    reader = csv.DictReader(f)
                    for row in reader:
                        ticket = Ticket(
                            ticket_code=int(row['TicketCode']),
                            flight_code=int(row['FlightCode']),
                            customer_id=int(row['CustomerID']),
                            customer_name=row['CustomerName'],
                            seat_type=row['SeatType'],
                            bought_time=datetime.strptime(row['BoughtTime'], "%Y/%m/%d %H:%M:%S")
                        )
                        self.ticketing_system.tickets.append(ticket)

            print("Data loaded successfully!")
            return True
        except Exception as e:
            print(f"Error loading data: {e}")
            return False

def main():
    # Initialize systems
    site_system = SiteSystem()
    route_system = RouteSystem()
    flight_system = FlightSystem() 
    ticketing_system = TicketingSystem()
    data_system = DataSystem(site_system, route_system, flight_system, ticketing_system)

    while True:
        print("\n=== Flight Management System ===")
        print("1. Site Management")
        print("2. Route Management") 
        print("3. Flight Management")
        print("4. Ticketing System")
        print("5. Save Data")
        print("6. Load Data")
        print("7. Exit")

        try:
            choice = int(input("Please select an option (1-7): "))
            if choice == 1:
                while True:
                    print("\n=== Site Management ===")
                    print("1. Add Site")
                    print("2. Delete Site") 
                    print("3. Show Site List")
                    print("4. Sort Sites")
                    print("5. Return to Main Menu")

                    sub_choice = int(input("Please select an option (1-5): "))
                    if sub_choice == 1:
                        site_system.add_site()
                    elif sub_choice == 2:
                        site_system.delete_site()
                    elif sub_choice == 3:
                        site_system.show_site_list()
                    elif sub_choice == 4:
                        site_system.sort_sites()
                    elif sub_choice == 5:
                        break
                    else:
                        print("Invalid choice!")

            elif choice == 2:
                while True:
                    print("\n=== Route Management ===")
                    print("1. Add Route")
                    print("2. Delete Route")
                    print("3. Modify Route")
                    print("4. Show Route List")
                    print("5. Sort Routes")
                    print("6. Return to Main Menu")

                    sub_choice = int(input("Please select an option (1-6): "))
                    if sub_choice == 1:
                        route_system.add_route()
                    elif sub_choice == 2:
                        route_system.delete_route()
                    elif sub_choice == 3:
                        route_system.modify_route()
                    elif sub_choice == 4:
                        route_system.site_system = site_system
                        route_system.show_route_list()
                    elif sub_choice == 5:
                        route_system.sort_routes()
                    elif sub_choice == 6:
                        break
                    else:
                        print("Invalid choice!")
            elif choice == 3:
                while True:
                    print("\n=== Flight Management ===")
                    print("1. Add Flight")
                    print("2. Delete Flight")
                    print("3. Modify Flight") 
                    print("4. Show Flight List")
                    print("5. Sort Flights")
                    print("6. Return to Main Menu")

                    sub_choice = int(input("Please select an option (1-6): "))
                    if sub_choice == 1:
                        flight_system.add_flight()
                    elif sub_choice == 2:
                        flight_system.delete_flight()
                    elif sub_choice == 3:
                        flight_system.modify_flight()
                    elif sub_choice == 4:
                        flight_system.site_system = site_system
                        flight_system.show_flight_list()
                    elif sub_choice == 5:
                        flight_system.sort_flights()
                    elif sub_choice == 6:
                        break
                    else:
                        print("Invalid choice!")
            elif choice == 4:
                while True:
                    print("\n=== Ticketing System ===")
                    print("1. Add Ticket")
                    print("2. Show Ticket List") 
                    print("3. Return to Main Menu")

                    sub_choice = int(input("Please select an option (1-3): "))
                    if sub_choice == 1:
                        ticketing_system.add_ticket()
                    elif sub_choice == 2:
                        ticketing_system.show_ticket_list()
                    elif sub_choice == 3:
                        break
                    else:
                        print("Invalid choice!")
            elif choice == 5:
                data_system.save_data()
            elif choice == 6:
                data_system.load_data()
            elif choice == 7:
                print("Thank you for using! Goodbye!")
                break
            else:
                print("Invalid choice!")

        except ValueError:
            print("Please enter a valid number!")
        except Exception as e:
            print(f"An error occurred: {e}")


if __name__ == "__main__":
    main()




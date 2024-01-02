Introduction:
The Final Version of the Flight Management System incorporates three essential entities: Flights, Passengers, and Seats. Building upon the foundations laid in the previous versions, the third version establishes crucial relationships between the Flights and Passengers entities, enriching the system's capabilities.
Entity Relationships:
1.	Flights Entity: The Flights entity serves as the core component, capturing and managing information related to each flight. It includes the following attributes: Flight ID, Departure Place, Arrival Place, and Departure Time. This entity acts as the primary container for flight-specific data.
2.	Passengers Entity: The Passengers entity represents individuals who book and board flights. It encompasses details such as Passenger ID, Name, Nationality, and Age. 
3.	Seats Entity: In this version, the introduction of the Seats entity further enhances the system's capacity to manage flight-related information by allotting a seat to a Passenger in a Flight. The Seats entity is intricately connected to both Flights and Passengers, serving as a bridge between them. It includes the following attributes: Passenger ID, Flight ID, Seat Number.

In this version, the three entities are placed in separate files and used as libraries by calling their functions in the main function. Moreover, Structures with Arrays have been used to handle the data.

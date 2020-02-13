package test1;


import java.sql.*;

public class Main 
	{
		static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
		static final String DB_URL = "jdbc:mysql://localhost/cs3207?serverTimezone=UTC&useSSL=false";

		  
		   static final String USER = "root";
		   static final String PASS = "cs3207";
		
		public static void main(String[] args)
			{
			Connection conn = null;
			   Statement stmt = null;
			   try{
			 
			      Class.forName("com.mysql.cj.jdbc.Driver");

			   conn = DriverManager.getConnection(DB_URL, USER, PASS);   
			      
			   stmt = conn.createStatement();
			   
//-------------------------------------------------------------------------------------------------------------------------------


			   //1. Create the tables and insert the proper data based on the provided data. You should make the movie, actor, director, and customer tables first and insert data into other related tables.
			   //step1. create tables.
			   //actor 테이블 생성
			   String create_actor_Table  = "CREATE TABLE actor " +
											"(actorID  INTEGER(10) NOT NULL AUTO_INCREMENT, " +
											"actorName VARCHAR(45) NOT NULL, " +
											"dateOfBirth date NOT NULL, " +
											"dateOfDeath date," +
											"gender VARCHAR(6) NOT NULL," +
											" PRIMARY KEY (actorID))"; 	  

			 	stmt.executeUpdate(create_actor_Table);



				//movie 테이블 생성
				String create_movie_table = "CREATE TABLE movie "+
								"(movieID Integer(10) NOT NULL AUTO_INCREMENT, "+
								"movieName VARCHAR(45) NOT NULL, " +
								"releaseYear Integer(10) NOT NULL, " +
								"releaseMonth Integer(10) NOT NULL, "+
								"releaseDate Integer(10) NOT NULL, "+
								"publisherName VARCHAR(45) NOT NULL, "+
								"avgRate Float, " +
								"Primary key (movieID))";

				stmt.executeUpdate(create_movie_table);


			 	//customer 테이블 생성
			 	String create_customer_Table = "CREATE TABLE customer "+
								"(customerID Integer(10) NOT NULL AUTO_INCREMENT, "+
								"customerName VARCHAR(45) NOT NULL, " +
								"dateOfBirth date NOT NULL, " +
								"gender VARCHAR(6) NOT NULL, "+
								"Primary key (customerID))";

				stmt.executeUpdate(create_customer_Table);


				//director 테이블 생성
				String create_director_table = "CREATE TABLE director "+
								"(directorID Integer(10) NOT NULL AUTO_INCREMENT, "+
								"directorName VARCHAR(45) NOT NULL, " +
								"dateOfBirth date NOT NULL, " +
								"dateOfDeath date, "+
								"Primary key (directorID))";

				stmt.executeUpdate(create_director_table);


				//casting 테이블 생성
				String create_casting_Table  = "CREATE TABLE casting " +
											"(movieID  INTEGER(10) NOT NULL, " +
											"actorID INTEGER(10) NOT NULL, " +
											"role VARCHAR(20) NOT NULL, " +
											"FOREIGN KEY (movieID) REFERENCES movie (movieID) ON DELETE CASCADE, " +
											"FOREIGN KEY (actorID) REFERENCES actor (actorID))"; 	  

			 	stmt.executeUpdate(create_casting_Table);

			 	//award 테이블 생성
			 	String create_award_Table  = "CREATE TABLE award " +
											"(awardID  INTEGER(10) AUTO_INCREMENT, " +
											"awardName VARCHAR(80), " +
											"PRIMARY KEY (awardID))";

			 	stmt.executeUpdate(create_award_Table);


				//actor Obtain 테이블 생성
			 	String create_actor_Obtain_Table  = "CREATE TABLE actorObtain " +
											"(actorID  INTEGER(10), " +
											"awardID INTEGER(10), " +
											"year INTEGER(5), " +
											"FOREIGN KEY (actorID) REFERENCES actor (actorID), " +
											"FOREIGN KEY (awardID) REFERENCES award (awardID))"; 	  

			 	stmt.executeUpdate(create_actor_Obtain_Table);
			 	


			 	//movieObtain 테이블 생성
			 	String create_movie_Obtain_Table  = "CREATE TABLE movieObtain " +
											"(movieID INTEGER(10), " +
											"awardID INTEGER(20), " +
											"year INTEGER(5), "  +
											"FOREIGN KEY (movieID) REFERENCES movie (movieID) ON DELETE CASCADE, "+
											"FOREIGN KEY (awardID) REFERENCES award (awardID))"; 	  

			 	stmt.executeUpdate(create_movie_Obtain_Table);


			 	//genre 테이블 생성
			 	String create_genre_Table  = "CREATE TABLE genre " +
											"(genreName VARCHAR(20) NOT NULL)"; 	  

			 	stmt.executeUpdate(create_genre_Table);

			    
			 	//movieGenre 테이블 생성
			    String create_movie_genre_Table  = "CREATE TABLE movieGenre " +
											"(movieID INTEGER(10) NOT NULL, " +
											"genreName VARCHAR(40) NOT NULL, " +
											"FOREIGN KEY (movieID) REFERENCES movie(movieID)ON DELETE CASCADE)"; 	  

			 	stmt.executeUpdate(create_movie_genre_Table);


			 	//make 테이블 생성
			 	String create_make_Table  = "CREATE TABLE make " +
											"(movieID INTEGER(10) NOT NULL, " +
											"directorID INTEGER(10) NOT NULL, " +
											"FOREIGN KEY (movieID) REFERENCES movie(movieID) ON DELETE CASCADE, " +
											"FOREIGN KEY (directorID) REFERENCES director(directorID))";


			 	stmt.executeUpdate(create_make_Table);


			 	//customerRate 테이블 생성
			 	String create_customer_Rate_Table  = "CREATE TABLE customerRate " +
											"(customerID INTEGER(10) NOT NULL, " +
											"movieID INTEGER(10) NOT NULL, " +
											"rate Float NOT NULL, " +
											"FOREIGN KEY (customerID) REFERENCES customer(customerID) ON DELETE CASCADE, " +
											"FOREIGN KEY (movieID) REFERENCES movie(movieID) ON DELETE CASCADE)";


			 	stmt.executeUpdate(create_customer_Rate_Table);


			 	//directorObtain 테이블 생성
			 	String create_director_Obtain_Table  = "CREATE TABLE directorObtain " +
											"(directorID INTEGER(10), " +
											"awardID INTEGER(10), " +
											"year INTEGER(10), " +
											"FOREIGN KEY (directorID) REFERENCES director(directorID), " +
											"FOREIGN KEY (awardID) REFERENCES award(awardID))";


			 	stmt.executeUpdate(create_director_Obtain_Table);
					System.out.println("Table created!");
//-------------------------------------------------------------------------------------------------------------			    

			    //step2. insert the data

			    //insert into actor's data  
				String actor_sql = "INSERT INTO actor " +
				   "VALUES ('10000001', 'Johnny Depp', '1963.06.09', '0000-00-00', 'Male')";
				
				stmt.executeUpdate(actor_sql);

				actor_sql = "INSERT INTO actor " +
				   "VALUES ('10000002', 'Winona Ryder', '1971.10.29', '0000-00-00', 'Female')";
				
				stmt.executeUpdate(actor_sql);

				actor_sql = "INSERT INTO actor " +
				   "VALUES ('10000003', 'Anne Hathaway', '1982.11.12', '0000-00-00', 'Female')";

				stmt.executeUpdate(actor_sql);

				actor_sql = "INSERT INTO actor " +
				   "VALUES ('10000004', 'Christian Bale', '1974.01.30', '0000-00-00', 'Male')";
				
				stmt.executeUpdate(actor_sql);

				actor_sql = "INSERT INTO actor " +
				   "VALUES ('10000005', 'Heath Ledger', '1979.04.04', '2008.1.22', 'Male')";
			
				stmt.executeUpdate(actor_sql);

				actor_sql = "INSERT INTO actor " +
				   "VALUES ('10000006', 'Jesse Eisenberg', '1983.10.5', '0000-00-00', 'Male')";

				stmt.executeUpdate(actor_sql);

				actor_sql = "INSERT INTO actor " +
				   "VALUES ('10000007', 'Andrew Garfield', '1983.08.20', '0000-00-00', 'Male')";

				stmt.executeUpdate(actor_sql);
				

				//insert into movie's data
				String movie_sql = "INSERT INTO movie " +
				   "VALUES ('20000001', 'Edward Scissorhands', '1991', '6', '29', '20th Century Fox Presents', '0')";

				stmt.executeUpdate(movie_sql);

				movie_sql = "INSERT INTO movie " +
					"VALUES ('20000002', 'Alice In Wonderland', '2010', '3', '4', 'Korea Sony Pictures', '0')";

				stmt.executeUpdate(movie_sql);

				movie_sql = "INSERT INTO movie " +
					"VALUES ('20000003', 'The Social Network', '2010', '11', '18', 'Korea Sony Pictures', '0')";

				stmt.executeUpdate(movie_sql);
				movie_sql = "INSERT INTO movie " +
				"VALUES ('20000004', 'The Dark Knight', '2008', '8', '6', 'Warner Brothers Korea', '0')";
					stmt.executeUpdate(movie_sql);


					//insert into customer's data
				String customer_sql = "INSERT INTO customer " +
					"VALUES ('30000001', 'Bob', '1997.11.14', 'Male')";

				stmt.executeUpdate(customer_sql);

				customer_sql = "INSERT INTO customer " +
					"VALUES ('30000002', 'John', '1978.01.23', 'Male')";

				stmt.executeUpdate(customer_sql);

				customer_sql = "INSERT INTO customer " +
					"VALUES ('30000003', 'Jack', '1980.05.04', 'Male')";

				stmt.executeUpdate(customer_sql);

				customer_sql = "INSERT INTO customer " +
					"VALUES ('30000004', 'Jill', '1981.04.17', 'Female')";

				stmt.executeUpdate(customer_sql);

				customer_sql = "INSERT INTO customer " +
					"VALUES ('30000005', 'Bell', '1990.05.14', 'Female')";

				stmt.executeUpdate(customer_sql);


				//insert into director data
				String director_sql = "INSERT INTO director " +
				   "VALUES ('40000001', 'Tim Burton', '1958.08.25', '0000-00-00')";

				stmt.executeUpdate(director_sql);
				
				director_sql = "INSERT INTO director " +
					"VALUES ('40000002', 'David Fincher', '1962.08.28', '0000-00-00')";

				stmt.executeUpdate(director_sql);

				director_sql = "INSERT INTO director " +
					"VALUES ('40000003', 'Christopher Nolan', '1970.07.30', '0000-00-00')";

				stmt.executeUpdate(director_sql);


				//insert into movieGenre data
				String movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000001', 'Fantasy')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000001', 'Romance')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000002', 'Fantasy')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000002', 'Adventure')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000002', 'Family')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000003', 'Drama')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000004', 'Action')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000004', 'Drama')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000004', 'Mystery')";

				stmt.executeUpdate(movieGenre_sql);

				movieGenre_sql = "INSERT INTO movieGenre " +
					"VALUES ('20000004', 'Thriller')";

				stmt.executeUpdate(movieGenre_sql);


				//insert into make data
				String make_sql = "INSERT INTO make (movieID, directorID) VALUES (20000001, 40000001)";

				stmt.executeUpdate(make_sql);

				make_sql = "INSERT INTO make (movieID, directorID) VALUES (20000002, 40000001)";

				stmt.executeUpdate(make_sql);

				make_sql = "INSERT INTO make (movieID, directorID) VALUES (20000003, 40000002)";

				stmt.executeUpdate(make_sql);

				make_sql = "INSERT INTO make (movieID, directorID) VALUES (20000004, 40000003)";

				stmt.executeUpdate(make_sql);

				System.out.println("Initial data inserted!");

				//insert into casting data
				String casting_sql = "INSERT INTO casting VALUES (20000001, 10000001, 'Main actor')";

				stmt.executeUpdate(casting_sql);

				casting_sql = "INSERT INTO casting VALUES (20000001, 10000002, 'Main actor')";

				stmt.executeUpdate(casting_sql);

				casting_sql = "INSERT INTO casting VALUES (20000002, 10000001, 'Main actor')";

				stmt.executeUpdate(casting_sql);

				casting_sql = "INSERT INTO casting VALUES (20000002, 10000003, 'Main actor')";

				stmt.executeUpdate(casting_sql);

				casting_sql = "INSERT INTO casting VALUES (20000003, 10000006, 'Main actor')";

				stmt.executeUpdate(casting_sql);

				casting_sql = "INSERT INTO casting VALUES (20000003, 10000007, 'Supporting actor')";

				stmt.executeUpdate(casting_sql);

				casting_sql = "INSERT INTO casting VALUES (20000004, 10000004, 'Main actor')";

				stmt.executeUpdate(casting_sql);

				casting_sql = "INSERT INTO casting VALUES (20000004, 10000005, 'Main actor')";

				stmt.executeUpdate(casting_sql);


				//Insert into genre data

				String genre_sql = "INSERT INTO genre VALUES ('Fantasy')";

				stmt.executeUpdate(genre_sql);

				genre_sql = "INSERT INTO genre VALUES ('Romance')";

				stmt.executeUpdate(genre_sql);

				genre_sql = "INSERT INTO genre VALUES ('Adventure')";

				stmt.executeUpdate(genre_sql);

				genre_sql = "INSERT INTO genre VALUES ('Family')";

				stmt.executeUpdate(genre_sql);

				genre_sql = "INSERT INTO genre VALUES ('Drama')";

				stmt.executeUpdate(genre_sql);

				genre_sql = "INSERT INTO genre VALUES ('Action')";

				stmt.executeUpdate(genre_sql);

				genre_sql = "INSERT INTO genre VALUES ('Mystery')";

				stmt.executeUpdate(genre_sql);

				genre_sql = "INSERT INTO genre VALUES ('Thriller')";

				stmt.executeUpdate(genre_sql);

				//insert directorObtain data

				String directorObtain_sql = "INSERT INTO directorObtain (directorID) VALUES ('40000001')";

				stmt.executeUpdate(directorObtain_sql);

				directorObtain_sql = "INSERT INTO directorObtain (directorID) VALUES ('40000002')";

				stmt.executeUpdate(directorObtain_sql);

				directorObtain_sql = "INSERT INTO directorObtain (directorID) VALUES ('40000003')";

				stmt.executeUpdate(directorObtain_sql);

//---------------------------------------------------------------
//2. Insert the proper data from the following statements.
for(int i= 1; i < 7 ; i ++) //sum of input is 5.
	{
			String str = "A";
			
			if(i == 1)
			{
				str = "Winona Ryder won the “Best supporting actor” award in 1994";
			}

			else if(i ==2)
			{
				str = "Andrew Garfield won the “Best supporting actor” award in 2011";
			}

			else if(i == 3)
			{
				str = "Jesse Eisenberg won the “Best main actor” award in 2011";
			}

			else if(i ==4)
			{
				str = "Johnny Depp won the “Best villain actor” award in 2011";
			}

			else if(i == 5)
			{
				str = "Edward Scissorhands won the “Best fantasy movie” award in 1991";
			}

			else if(i == 6)
			{
				str = "Alice In Wonderland won the “Best fantasy movie” award in 2011";
			}
			

			String result_name = str.substring(0,str.lastIndexOf("won")-1); //사람이름은 won 단어 이전에서 cut
			String result_award = str.substring(str.lastIndexOf("the") + 5, str.lastIndexOf("award")-2); //award name cut
			String result_year = str.substring(str.length()-4, str.length()); //year cut

		System.out.println("Statement: " + str);  

			 if(str.contains("actor")) //actor 해당되는 경우
			 {
			 	
				 String insert_nameID_sql = "INSERT INTO actorObtain (actorID) " + 
						   "SELECT actorID FROM actor WHERE actorName ="+ "\"" + result_name + "\"";	//actor의 name과 id값을 비교해 actorobtain에 id삽입

						stmt.executeUpdate(insert_nameID_sql);

						System.out.println("Translated SQL: INSERT INTO actorObtain (actorID) SELECT actorID FROM actor WHERE actorName = " + result_name + ";");

				String insert_award_name = "INSERT INTO award(awardName)" +
				"select(" + "\""+ result_award + "\"" + ") WHERE NOT EXISTS (SELECT* from award where awardName =" + "\"" + result_award + "\")"; //awardname insert

				stmt.executeUpdate(insert_award_name);

				System.out.println("Translated SQL: INSERT INTO award (awardName) SELECT(" +result_award + "WHERE NOT EXISTS (SELECT* FROM award WHERE awardName = "+result_award + ";");


				String insert_awardID_sql = "update actorObtain " +
				   "set awardID = (select awardID FROM award where awardName =" + "\"" +result_award + "\"" + ")" + //awardname이용해 actorobtain에 awardID insert
				   "where awardID is NULL";
				  stmt.executeUpdate(insert_awardID_sql);

				  System.out.println("Translated SQL: UPDATE actorObtain SET awardID = (SELECT awardID FROM award where awardName = " + result_award +") WHERE awardID is NULL;");


				String insert_year_sql = "UPDATE actorObtain " +
					"set year =" + "\""+result_year+"\"" + "where year is NULL";	//year insert

					stmt.executeUpdate(insert_year_sql);

					System.out.println("Translated SQL: UPDATE actorObtain SET year = " + result_year+"WHERE year is NULL;");

					System.out.println("Updated tables");
			

					String print_table= "Select * from award";

					System.out.println("award table");
					 System.out.println("------------------------------------------------");
					
            ResultSet rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%-30s","awardID","\t\tawardName"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%-30s",rs.getString(1),"\t\t" + rs.getString(2)));

                }
                while(rs.next());
            }
            else
            {
               
            }

            System.out.println("------------------------------------------------");
            
            System.out.println("actorObtain table");
            System.out.println("------------------------------------------------");
            print_table="Select * from actorObtain";

        
            rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","actorID","awardID","year"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), rs.getString(2), rs.getString(3)));
                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("------------------------------------------------");

            
			 }
			

           
			
        else	//movie의 해당되는 경우
        {
            String insert_movieID_sql = "INSERT INTO movieObtain (movieID) " +
						   "SELECT movieID FROM movie WHERE movieName ="+ "\"" + result_name + "\"";

						stmt.executeUpdate(insert_movieID_sql);

						System.out.println("Translated SQL: INSERT INTO movieObtain (movieID) SELECT movieID FROM movie WHERE movieName = " + result_name + ";");

						String insert_award_name = "INSERT INTO award(awardName)" +
								"select(" + "\""+ result_award + "\"" + ") WHERE NOT EXISTS (SELECT* from award where awardName =" + "\"" + result_award + "\")"; //awardname insert

				stmt.executeUpdate(insert_award_name);

				System.out.println("Translated SQL: INSERT INTO award (awardName) SELECT(" +result_award + "WHERE NOT EXISTS (SELECT* FROM award WHERE awardName = "+result_award + ";");

				String insert_awardID_sql = "update movieObtain " +
				   "set awardID = (select awardID FROM award where awardName =" + "\"" +result_award + "\"" + ")" +
				   "where awardID is NULL";
				  stmt.executeUpdate(insert_awardID_sql);

				  System.out.println("Translated SQL: UPDATE movieObtain SET awardID = (SELECT awardID FROM award where awardName = " + result_award +") WHERE awardID is NULL;");


				String insert_year_sql = "UPDATE movieObtain " +
					"set year =" + "\""+result_year+"\"" + "where year is NULL";

					stmt.executeUpdate(insert_year_sql);

					System.out.println("Translated SQL: UPDATE movieObtain SET year = " + result_year+"WHERE year is NULL;");
					
				

					System.out.println("Updated tables");
					
					String print_table= "Select * from award";

					System.out.println("award table");
					 System.out.println("------------------------------------------------");
					
            ResultSet rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%-30s","awardID","\t\tawardName"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%-30s",rs.getString(1),"\t\t" + rs.getString(2)));

                }
                while(rs.next());
            }
            else
            {
               
            }

            System.out.println("------------------------------------------------");
            
            System.out.println("movieObtain table");
            System.out.println("------------------------------------------------");
            print_table="Select * from movieObtain";

        
            rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","movieID","awardID","year"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), rs.getString(2), rs.getString(3)));
                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("------------------------------------------------");
        }

        
			
}

//3. Insert data to the proper tables based on the following statements and update avgRate if necessary.

		//3.1
//3.1

String insert_customerRate= "INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Bob'),"
		+ "(SELECT movieID FROM movie WHERE movieName = 'The Dark Knight'),  5)";

stmt.executeUpdate(insert_customerRate);

System.out.println("Statement: Bob rates 5 to “The Dark Knight”.");
		System.out.println("Translated SQL: INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Bob'),"
				+ "(SELECT movieID FROM movie WHERE movieName = 'The Dark Knight'),  5);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		String print_table= "Select * from customerRate";
		 ResultSet rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","customerID","movieID","     "+"rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), "     "+rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

String insert_movie_avgRate = "UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Bob') ) WHERE movieID ="
		+ "(SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Bob')))";
stmt.executeUpdate(insert_movie_avgRate);

		System.out.println("Translated SQL: UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE customerID =(SELECT customerID FROM customer WHERE customerName = 'Bob') ) WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Bob')));");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from movie";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%10s%20s%20s%13s%12s%15s%18s", "movieID","movieName","releaseYear","releaseMonth","releaseDate","publisherName","avgRate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s%12s%28s%10s",rs.getString(1), "     "+rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5), rs.getString(6),rs.getString(7)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");
//3.2
insert_customerRate= "INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Bell'),"
		+ "(SELECT movieID FROM make WHERE directorID = (SELECT directorID FROM director WHERE directorName = 'Tim Burton') LIMIT 0, 1),  5)";
stmt.executeUpdate(insert_customerRate);

System.out.println("Statement: Bell rates 5 to the movies whose director is “Tim Burton”.");
		System.out.println("Translated SQL: INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Bell') (SELECT movieID FROM make WHERE directorID = (SELECT directorID FROM director WHERE directorName = 'Tim Burton') LIMIT 0, 1),  5);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from customerRate";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","customerID","movieID","     "+"rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), "     "+rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

insert_customerRate= "INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Bell'),"
		+ "(SELECT movieID FROM make WHERE directorID = (SELECT directorID FROM director WHERE directorName = 'Tim Burton') LIMIT 1, 1),  5)";
stmt.executeUpdate(insert_customerRate);

System.out.println("Statement: Bell rates 5 to the movies whose director is “Tim Burton”.");
		System.out.println("Translated SQL: INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Bell')(SELECT movieID FROM make WHERE directorID = (SELECT directorID FROM director WHERE directorName = 'Tim Burton') LIMIT 1, 1),  5);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("------------------------------------------------");
		print_table= "Select * from customerRate";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","customerID","movieID","     "+"rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), "     "+rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("------------------------------------------------");

insert_movie_avgRate = "UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Bell') ) WHERE movieID ="
		+ "(SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Bell') LIMIT 0,1))";

stmt.executeUpdate(insert_movie_avgRate);

System.out.println("Translated SQL: UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE customerID =(SELECT customerID FROM customer WHERE customerName = 'Bell') ) WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Bell') LIMIT 0,1));");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("------------------------------------------------");
		print_table= "Select * from movie";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%10s%20s%20s%13s%12s%15s%18s", "movieID","movieName","releaseYear","releaseMonth","releaseDate","publisherName","avgRate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s%12s%28s%10s",rs.getString(1), "     "+rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5), rs.getString(6),rs.getString(7)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("------------------------------------------------");

insert_movie_avgRate = "UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Bell') ) WHERE movieID ="
		+ "(SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Bell') LIMIT 1,1))";

stmt.executeUpdate(insert_movie_avgRate);

System.out.println("Translated SQL: UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE customerID =(SELECT customerID FROM customer WHERE customerName = 'Bell') ) WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Bell') LIMIT 1,1));");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from movie";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%10s%20s%20s%13s%12s%15s%18s", "movieID","movieName","releaseYear","releaseMonth","releaseDate","publisherName","avgRate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s%12s%28s%10s",rs.getString(1), "     "+rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5), rs.getString(6),rs.getString(7)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

//3.3
insert_customerRate= "INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Jill'),"
		+ "(SELECT movieID FROM casting WHERE actorId = (SELECT actorId FROM actor WHERE gender = 'female' LIMIT 0,1)),  4)";

stmt.executeUpdate(insert_customerRate);

System.out.println("Statement: Jill rates 4 to the movies whose main actor is female.");
		System.out.println("Translated SQL: INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Jill') (SELECT movieID FROM casting WHERE actorId = (SELECT actorId FROM actor WHERE gender = 'female' LIMIT 0,1)),  4);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from customerRate";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","customerID","movieID","     "+"rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), "     "+rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

insert_customerRate= "INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Jill'),"
		+ "(SELECT movieID FROM casting WHERE actorId = (SELECT actorId FROM actor WHERE gender = 'female' LIMIT 1,1)),  4)";

stmt.executeUpdate(insert_customerRate);
System.out.println("Statement: Jill rates 4 to the movies whose main actor is female.");
		System.out.println("Translated SQL: INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Jill') (SELECT movieID FROM casting WHERE actorId = (SELECT actorId FROM actor WHERE gender = 'female' LIMIT 1,1)),  4);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from customerRate";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","customerID","movieID","     "+"rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), "     "+rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");
insert_movie_avgRate = "UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE movieID ="
		+ "(SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jill') LIMIT 0,1))"
		+ "WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Jill')LIMIT 0,1) LIMIT 0, 1)";

stmt.executeUpdate(insert_movie_avgRate);

System.out.println("UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE movieID =(SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jill') LIMIT 0,1)) WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jill')LIMIT 0,1) LIMIT 0, 1);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from movie";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%10s%20s%20s%13s%12s%15s%18s", "movieID","movieName","releaseYear","releaseMonth","releaseDate","publisherName","avgRate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s%12s%28s%10s",rs.getString(1), "     "+rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5), rs.getString(6),rs.getString(7)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

insert_movie_avgRate = "UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE movieID ="
		+ "(SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jill') LIMIT 1,1))"
		+ "WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Jill')LIMIT 1,1) LIMIT 1,1)";

stmt.executeUpdate(insert_movie_avgRate);

System.out.println("UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE movieID =(SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jill') LIMIT 1,1)) WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jill')LIMIT 1,1) LIMIT 1, 1);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from movie";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%10s%20s%20s%13s%12s%15s%18s", "movieID","movieName","releaseYear","releaseMonth","releaseDate","publisherName","avgRate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s%12s%28s%10s",rs.getString(1), "     "+rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5), rs.getString(6),rs.getString(7)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

//3.4
insert_customerRate= "INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Jack'),"
		+ "(SELECT movieID FROM movieGenre WHERE genreName LIKE '%Fantasy%' LIMIT 0,1),  4)";

stmt.executeUpdate(insert_customerRate);
System.out.println("Statement: Jack rates 4 to the fantasy movies;");
		System.out.println("Translated SQL: INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Jack') (SELECT movieID FROM movieGenre WHERE genreName LIKE '%Fantasy%' LIMIT 0,1),  4);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from customerRate";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","customerID","movieID","     "+"rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), "     "+rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

insert_customerRate= "INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Jack'),"
		+ "(SELECT movieID FROM movieGenre WHERE genreName LIKE '%Fantasy%' LIMIT 1,1),  4)";

stmt.executeUpdate(insert_customerRate);

System.out.println("Statement: Jack rates 4 to the fantasy movies;");
		System.out.println("Translated SQL: INSERT INTO customerRate VALUES ((SELECT customerID FROM customer WHERE customerName = 'Jack') (SELECT movieID FROM movieGenre WHERE genreName LIKE '%Fantasy%' LIMIT 1,1),  4);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from customerRate";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%7s%10s%7s","customerID","movieID","     "+"rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%7s%10s%7s",rs.getString(1), "     "+rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

 insert_movie_avgRate = "UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE movieID ="
 		+ "(SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jack') LIMIT 0,1))"
 		+ "WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID ="
 		+ "(SELECT customerID FROM customer WHERE customerName = 'Jill')LIMIT 0,1) LIMIT 0, 1)";

stmt.executeUpdate(insert_movie_avgRate);

System.out.println("UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jack') LIMIT 0,1)) WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jill')LIMIT 0,1) LIMIT 0, 1);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from movie";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%10s%20s%20s%13s%12s%15s%18s", "movieID","movieName","releaseYear","releaseMonth","releaseDate","publisherName","avgRate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s%12s%28s%10s",rs.getString(1), "     "+rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5), rs.getString(6),rs.getString(7)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");

insert_movie_avgRate = "UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE movieID ="
		+ "(SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jack') LIMIT 1,1))"
		+ "WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID ="
		+ "(SELECT customerID FROM customer WHERE customerName = 'Jill')LIMIT 1,1) LIMIT 1, 1)";

stmt.executeUpdate(insert_movie_avgRate);
			      
System.out.println("UPDATE movie SET avgrate = (SELECT avg(rate) FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jack') LIMIT 1,1)) WHERE movieID = (SELECT movieID FROM customerRate WHERE movieID = (SELECT movieID FROM customerRate WHERE customerID = (SELECT customerID FROM customer WHERE customerName = 'Jill')LIMIT 1,1) LIMIT 1, 1);");
		System.out.println("Updated tables");
		System.out.println("customerRate Table");
		System.out.println("-------------------------------------------------------------------------------------------------------------");
		print_table= "Select * from movie";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%10s%20s%20s%13s%12s%15s%18s", "movieID","movieName","releaseYear","releaseMonth","releaseDate","publisherName","avgRate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s%12s%28s%10s",rs.getString(1), "     "+rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5), rs.getString(6),rs.getString(7)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("-------------------------------------------------------------------------------------------------------------");
//-------------------------------------------------------------------------------------------------------------------------------------------------------
		   //4. Select the names of the movies whose actor are dead.
            String select_dead_actor = "Select movieName from movie where movieID = (Select movieID from casting where actorID = (Select actorID from actor where dateOfdeath NOT in ('0000-00-00')))";

            stmt.executeQuery(select_dead_actor);

            System.out.println("Statement: Select the names of the movies whose actor are dead.");
            		System.out.println("Translated SQL: Select movieName from movie where movieID = (Select movieID from casting where actorID = (Select actorID from actor where dateOfdeath NOT in ('0000-00-00')));");
            		System.out.println("Select tables");
            		
            		System.out.println("---------------------");
            		   rs = stmt.executeQuery(select_dead_actor);
                        if(rs.next())
            			   System.out.println(String.format(rs.getString(1)));
                        
                        System.out.println("---------------------");
//----------------------------------------------------------------------------------------------------------------------------------------
             //5. Select the names of the directors who cast the same actor more than once.
                        String select_more_director = "SELECT directorName FROM director WHERE directorID = ANY(SELECT directorID from make where movieID = ANY(SELECT movieID FROM casting WHERE actorID = (SELECT actorID FROM casting GROUP BY actorID HAVING COUNT(movieID)>1)))";

                        stmt.executeQuery(select_more_director);

                        System.out.println("Statement: Select the names of the directors who cast the same actor more than once.");
                        		System.out.println("Translated SQL: SELECT directorName FROM director WHERE directorID = ANY(SELECT directorID from make where movieID = ANY(SELECT movieID FROM casting WHERE actorID = (SELECT actorID FROM casting GROUP BY actorID HAVING COUNT(movieID)>1)));");
                        		System.out.println("Select tables");
                        		
                        		System.out.println("---------------------");
                        		   rs = stmt.executeQuery(select_more_director);
                                    if(rs.next())
                        			   System.out.println(String.format(rs.getString(1)));
                                    
                                    System.out.println("---------------------");

//-----------------------------------------------------------------------------------------------------------------------------------------------------
              //6. Select the names of the movies and the genres, where movies have the common genre.
                                    String select_same_genre_and_movie = "SELECT movie.movieName, T.genreName from movie, (SELECT movieID, genreName FROM movieGenre where genreName = ANY(SELECT genreName FROM movieGenre GROUP BY genreName HAVING COUNT(genreName)>1)) AS T WHERE T.MOVIEID = MOVIE.MOVIEID";

                                    stmt.executeQuery(select_same_genre_and_movie);

                                    System.out.println("Statement: Select the names of the movies and the genres, where movies have the common genre.");
                        		System.out.println("Translated SQL: SELECT movie.movieName, T.genreName from movie, (SELECT movieID, genreName FROM movieGenre where genreName = ANY(SELECT genreName FROM movieGenre GROUP BY genreName HAVING COUNT(genreName)>1)) AS T WHERE T.MOVIEID = MOVIE.MOVIEID;");
                        		System.out.println("Select tables");
                        		
                        		  System.out.println("----------------------------------------------------------");

                        		  print_table= "SELECT movie.movieName, T.genreName from movie, (SELECT movieID, genreName FROM movieGenre where genreName = ANY(SELECT genreName FROM movieGenre GROUP BY genreName HAVING COUNT(genreName)>1)) AS T WHERE T.MOVIEID = MOVIE.MOVIEID";
		rs = stmt.executeQuery(print_table);

            System.out.println(String.format("%10s%20s", "movieName","\t\tGenreName"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s",rs.getString(1), rs.getString(2)));

                }
                while(rs.next());
            }
            else
            {
               
            }
            System.out.println("----------------------------------------------------------");
//----------------------------------------------------------------------------------------------------------------------------------------------
            //7.Delete the movies whose director or actor did not get any award and delete data from related tables.

            String delete_no_award_movie_data = "delete from movie WHERE movieID IN (SELECT movieID FROM ((SELECT movie.movieID from movie NATURAL JOIN (SELECT R.movieID FROM (SELECT T.movieID FROM (select casting.movieID, casting.actorID, actorObtain.awardID from casting LEFT JOIN actorObtain ON casting.actorid = actorObtain.actorID) AS T  where  T.awardID is NULL) AS R GROUP BY R.movieID HAVING COUNT(R.movieID) > 1) AS Q WHERE movie.movieID = Q.movieID) UNION (SELECT make.movieID from make LEFT JOIN (SELECT A.directorID FROM (SELECT director.directorID, directorObtain.awardID FROM director LEFT JOIN directorObtain ON director.directorID = directorObtain.directorID) AS A where A.awardID is NULL) AS B  ON make.directorID = B.directorID)) tmp)";

            stmt.executeUpdate(delete_no_award_movie_data);

             System.out.println("Statement: Delete the movies whose director or actor did not get any award and delete data from related tables.");
                        		System.out.println("Translated SQL: delete from movie WHERE movieID IN (SELECT movieID FROM ((SELECT movie.movieID from movie NATURAL JOIN (SELECT R.movieID FROM (SELECT T.movieID FROM (select casting.movieID, casting.actorID, actorObtain.awardID from casting LEFT JOIN actorObtain ON casting.actorid = actorObtain.actorID) AS T  where  T.awardID is NULL) AS R GROUP BY R.movieID HAVING COUNT(R.movieID) > 1) AS Q WHERE movie.movieID = Q.movieID) UNION (SELECT make.movieID from make LEFT JOIN (SELECT A.directorID FROM (SELECT director.directorID, directorObtain.awardID FROM director LEFT JOIN directorObtain ON director.directorID = directorObtain.directorID) AS A where A.awardID is NULL) AS B  ON make.directorID = B.directorID)) tmp);");

                        		System.out.println("delete tables");
                        		
                        		  System.out.println("----------------------------------------------------------");
                        		  System.out.println("movie table");
                        		  print_table= "select* from movie";
		rs = stmt.executeQuery(print_table);

          System.out.println(String.format("%10s%20s%20s%13s%12s%15s%18s", "movieID","movieName","releaseYear","releaseMonth","releaseDate","publisherName","avgRate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s%12s%28s%10s",rs.getString(1), "     "+rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5), rs.getString(6),rs.getString(7)));

                }
                while(rs.next());
            }
        
            System.out.println("---------------------------------------------");
            			 System.out.println("casting table");

                        		  print_table= "select* from casting";
		rs = stmt.executeQuery(print_table);

          System.out.println(String.format("%10s%20s%20s", "movieID","actorID","role"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s",rs.getString(1),rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
        
            System.out.println("---------------------------------");
 System.out.println("movieObtain table");
             print_table= "select* from movieObtain";
		rs = stmt.executeQuery(print_table);

          System.out.println(String.format("%10s%20s%20s", "actorID","awardID","year"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s",rs.getString(1),rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
        
            System.out.println("---------------------------------");
 System.out.println("moviegenre table");
            print_table= "select* from moviegenre";
		rs = stmt.executeQuery(print_table);

          System.out.println(String.format("%10s%20s", "movieID","genreName"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s",rs.getString(1),rs.getString(2)));

                }
                while(rs.next());
            }
        
            System.out.println("---------------------------------");
 System.out.println("make table");

             print_table= "select* from make";
		rs = stmt.executeQuery(print_table);

          System.out.println(String.format("%10s%20s", "movieID","directorID"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s",rs.getString(1),rs.getString(2)));

                }
                while(rs.next());
            }
        
            System.out.println("---------------------------------");

 System.out.println("customerRate table");
            print_table= "select* from customerRate";
		rs = stmt.executeQuery(print_table);

          System.out.println(String.format("%10s%20s%20s", "customerID","movieID","rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s",rs.getString(1),rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
//----------------------------------------------------------------------------
            //8. Delete all customers and delete data from related tables.

            String delete_related_customer = "Delete FROM customer";

             stmt.executeUpdate(delete_related_customer);

             System.out.println("Statement: Delete all customers and delete data from related tables.");
                        		System.out.println("Translated SQL: Delete FROM customer;");

                        		System.out.println("delete tables");
                        		
                        		  System.out.println("----------------------------------------------------------");
                        		  System.out.println("customer table");
                        		  print_table= "select* from customer";
		rs = stmt.executeQuery(print_table);

          System.out.println(String.format("%10s%20s%20s%13s", "customerID","customerName","dateOfBirth","gender"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s%13s",rs.getString(1), rs.getString(2), rs.getString(3), rs.getString(4)));

                }
                while(rs.next());
            }
        
            System.out.println("---------------------------------------------------------------");

            System.out.println("customerrate table");
                        		  print_table= "select* from customerRate";
		rs = stmt.executeQuery(print_table);

          System.out.println(String.format("%10s%20s%20s", "customerID","movieID","rate"));
            if(rs.next())
            {
                do
                {
                    System.out.println(String.format("%10s%20s%10s",rs.getString(1), rs.getString(2), rs.getString(3)));

                }
                while(rs.next());
            }
        
            System.out.println("-------------------------------------------------------------------");

//-----------------------------------------------------------------------
            //drop the all tables
            String drop_all_tables = "drop table actorObtain";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table movieObtain";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table movieGenre";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table customerRate";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table directorObtain";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table make";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table casting";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table movie";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table actor";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table director";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table award";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table genre";
            stmt.executeUpdate(drop_all_tables);
            
            drop_all_tables = "drop table customer";
            stmt.executeUpdate(drop_all_tables);
       

            System.out.println("drop the all tables");

			   }catch(SQLException se){
		      //Handle errors for JDBC
		      se.printStackTrace();
		   }catch(Exception e){
		      //Handle errors for Class.forName
		      e.printStackTrace();
		   }finally{
		      //finally block used to close resources
		      try{
		         if(stmt!=null)
		            conn.close();
		      }catch(SQLException se){
		      }// do nothing
		      try{
		         if(conn!=null)
		            conn.close();
		      }catch(SQLException se){
		         se.printStackTrace();
		      }
		   }
	
		}
			}


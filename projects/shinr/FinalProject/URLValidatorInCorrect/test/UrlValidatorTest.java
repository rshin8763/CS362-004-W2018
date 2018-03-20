
import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {


	public UrlValidatorTest(String testName) {
		super(testName);
	}



	public void testManualTest()
	{
		//Manual Test: Used prints besides asserts because it
	     //was much easier to read 
	    //scheme that is basically the same the as the 		  
	   //default scheming in the UrlValidator Code
	   String[] schemes = {"https", "http", "ftp"};
	   //url Validator 1 test to test the 1st scheming
	   UrlValidator urlVal = new UrlValidator(schemes);
	   	System.out.print("\"urVal: Test 1\"");
	    if (urlVal.isValid("http://www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 2\"");
		if (urlVal.isValid("http://www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 3\"");
		if (urlVal.isValid("http://www.bank/../")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 4\"");
		if (urlVal.isValid("http://www.google.com/../")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 5\"");
		if (urlVal.isValid("http://www.bank:80")) {
	   		System.out.println("url is valid");
			} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 7\"");
		if (urlVal.isValid("http:/www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 8\"");
		if (urlVal.isValid("http:/www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 9\"");
		if (urlVal.isValid("http://www.go.au")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
		System.out.print("\"urlVal: Test 10\"");
		if (urlVal.isValid("http://www.bank:65535")) {
	   		System.out.println("url is valid");
			} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 11\"");
		if (urlVal.isValid("http://www.google.com:65535")) {
			System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 12\"");
		if (urlVal.isValid("http:/www.bank?action=edit&mode=up")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 13\"");
		if (urlVal.isValid("http:/www.google.com?action=edit&mode=up")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 14\"");
		if (urlVal.isValid("http:/www.bank/test1")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 15\"");
		if (urlVal.isValid("http:/www.google.com/test1")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 16\"");
		if (urlVal.isValid("http:/www.bank:0?action=edit&mode=up")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 17\"");
		if (urlVal.isValid("http:/www.google.com:0?action=edit&mode=up")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 18\"");
		if (urlVal.isValid("http:/www.bank:0")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 19\"");
		if (urlVal.isValid("http:/www.google.com:0")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 20\"");
		if (urlVal.isValid("http:/www.bank:80?action=edit&mode=up")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 21\"");
		if (urlVal.isValid("http:/www.google.com:80?action=edit&mode=up")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 22\"");
		if (urlVal.isValid("http:/www.bank:65535?action=edit&mode=up")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 23\"");
		if (urlVal.isValid("http:/www.google.com:65535?action=edit&mode=up")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 24\"");
		if (urlVal.isValid("http://www.255.255.255.255.com")) 			{
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 25\"");
		if (urlVal.isValid("http://www.yahoo.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 26\"");
		if (urlVal.isValid("http:/www.!fu")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 27\"");
		if (urlVal.isValid("https://www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 28\"");
		if(urlVal.isValid("h3t://www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 29\"");
		if (urlVal.isValid("h3t://www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 30\"");
		if (urlVal.isValid("https://www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 31\"");
		if (urlVal.isValid("ftp://www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal: Test 32\"");
		if (urlVal.isValid("ftp://www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		}; 
		//url Validator 2 test to test the second scheming method
		UrlValidator urlVal2 = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   	System.out.print("\"urlVal: Test 6\"");
		if (urlVal.isValid("http://www.google.com:80")) {
			System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	  	System.out.print("\"urlVal2: Test 1\"");
	    if (urlVal2.isValid("http://www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 2\"");
		if (urlVal2.isValid("http://www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 3\"");
		if (urlVal2.isValid("http://www.bank/../")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 4\"");
		if (urlVal2.isValid("http://www.google.com/../")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 5\"");
		if (urlVal2.isValid("http://www.bank:80")) {
	   		System.out.println("url is valid");
			} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 6\"");
		if (urlVal2.isValid("http://www.google.com:80")) {
			System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 7\"");
		if (urlVal2.isValid("http:/www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 8\"");
		if (urlVal2.isValid("http:/www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 9\"");
		if (urlVal2.isValid("http://www.go.au")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
		System.out.print("\"urlVal2: Test 10\"");
		if (urlVal2.isValid("http://www.bank:65535")) {
	   		System.out.println("url is valid");
			} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 11\"");
		if (urlVal2.isValid("http://www.google.com:65535")) {
			System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 12\"");
		if (urlVal2.isValid("http:/www.bank?action=edit&mode=up")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 13\"");
		if (urlVal2.isValid("http:/www.google.com?action=edit&mode=up")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 14\"");
		if (urlVal2.isValid("http:/www.bank/test1")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 15\"");
		if (urlVal2.isValid("http:/www.google.com/test1")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 16\"");
		if (urlVal2.isValid("http:/www.bank:0?action=edit&mode=up")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 17\"");
		if (urlVal2.isValid("http:/www.google.com:0?action=edit&mode=up")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 18\"");
		if (urlVal2.isValid("http:/www.bank:0")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 19\"");
		if (urlVal2.isValid("http:/www.google.com:0")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 20\"");
		if (urlVal2.isValid("http:/www.bank:80?action=edit&mode=up")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 21\"");
		if (urlVal2.isValid("http:/www.google.com:80?action=edit&mode=up")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 22\"");
		if (urlVal2.isValid("http:/www.bank:65535?action=edit&mode=up")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 23\"");
		if (urlVal2.isValid("http:/www.google.com:65535?action=edit&mode=up")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 24\"");
		if (urlVal2.isValid("http://www.255.255.255.255.com")) 		{
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 25\"");
		if (urlVal2.isValid("http://www.yahoo.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 26\"");
		if (urlVal2.isValid("http:/www.!fu")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 27\"");
		if (urlVal2.isValid("https://www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 28\"");
		if(urlVal2.isValid("h3t://www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 29\"");
		if (urlVal2.isValid("h3t://www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 30\"");
		if (urlVal2.isValid("https://www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 31\"");
		if (urlVal2.isValid("ftp://www.bank")) {
		   		System.out.println("url is valid");
		} else {
				System.out.println("url is invalid");
		};
	   	System.out.print("\"urlVal2: Test 32\"");
		if (urlVal2.isValid("ftp://www.google.com")) {
	   		System.out.println("url is valid");
		} else {
			System.out.println("url is invalid");
		}; 	

	}


	public void testSchemePartitions()
	{
		// Test Scheme Partitions
		System.out.print("----- Default Scheme Partition Tests ------\n");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

		boolean testFail = false;

		try {

			System.out.print("Test http -- ");
			if(!urlVal.isValid("http://google.com")){
				testFail = true;
				System.out.print("FAIL\n");
			} else System.out.print("PASS\n");

			System.out.print("Missing : -- ");
			if(urlVal.isValid("http//google.com")){
				testFail = true;
				System.out.print("FAIL\n");
			} else System.out.print("PASS\n");

			System.out.print("Missing / -- ");
			if(urlVal.isValid("http:/google.com")){
				testFail = true;
				System.out.print("FAIL\n");
			} else System.out.print("PASS\n");

			System.out.print("Missing // -- ");
			if(urlVal.isValid("http:google.com")){
				testFail = true;
				System.out.print("FAIL\n");
			} else System.out.print("PASS\n");

			System.out.print("Empty Scheme -- ");
			if(urlVal.isValid("google.com")){
				testFail = true;
				System.out.print("FAIL\n");
			} else System.out.print("PASS\n");

			System.out.print("Test ftp -- ");
			if(!urlVal.isValid("ftp://google.com")){
				testFail = true;
				System.out.print("FAIL\n");
			} else System.out.print("PASS\n");

			System.out.print("Test alphanumeric starting with letter -- ");
			if(!urlVal.isValid("f3p://google.com")){
				testFail = true;
				System.out.print("FAIL\n");
			} else System.out.print("PASS\n");

			System.out.print("Test alphanumeric starting with number -- ");
			if(urlVal.isValid("3p://google.com")){
				testFail = true;
				System.out.print("FAIL\n");
			} else System.out.print("PASS\n");


		} catch (Error e) {
			//There is an error with regex.
			System.out.print("ERROR\n");
			testFail = true;
		}


		System.out.println("");
		assertFalse(testFail);
	}

	public void testAuthorityPartitions(){
		// Test Authority Partitions
		System.out.print("----- Authority Partition Test ------\n"); 
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		boolean testFail = false;

		System.out.print("No authentication -- ");
		if(!urlVal.isValid("http://google.com")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Incorrect authentication -- ");
		if(urlVal.isValid("user::password@http://google.com")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Domain name host -- ");
		if(!urlVal.isValid("http://google.com")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("IPv4 Address Host -- ");
		if(!urlVal.isValid("http://192.168.0.1")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Invalid IPv4 Address Host (Greater than 255) -- ");
		if(urlVal.isValid("http://300.0.0.0")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Invalid IPv4 Address Host (Only 3 decimals) -- ");
		if(urlVal.isValid("http://0.0.0")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.println("");
		assertFalse(testFail);
	}

	public void testPathPartitions(){
		System.out.print("----- Path Partition Test ------\n"); 
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		boolean testFail = false;

		System.out.print("Valid Path /ok -- ");
		if(!urlVal.isValid("http://google.com/ok")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("invalid Path // -- ");
		if(urlVal.isValid("http://google.com//")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("invalid Path / / (whitespace)-- ");
		if(urlVal.isValid("http://google.com/ /")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("valid Path /ab/da -- ");
		if(!urlVal.isValid("http://google.com/ab/da")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.println("");
		assertFalse(testFail);

	}

	public void testQueryPartitions(){
		System.out.print("----- Query Partition Test ------\n"); 
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		boolean testFail = false;

		System.out.print("No query -- ");
		if(!urlVal.isValid("http://google.com")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("No query parameters -- ");
		if(!urlVal.isValid("http://google.com?")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("valid incomplete pair -- ");
		if(!urlVal.isValid("http://google.com?hello=")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Valid Query (1 parameter) -- ");
		if(!urlVal.isValid("http://google.com?name=ryan")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Valid Query (parameter with numeric values) -- ");
		if(!urlVal.isValid("http://google.com?value=4")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Valid Query (2 parameters) -- ");
		if(!urlVal.isValid("http://google.com?name=Ryan&value=10")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.println("");
		assertFalse(testFail);
	}

	public void testPortPartitions(){
		System.out.print("----- Port Partition Test ------\n"); 
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		boolean testFail = false;

		System.out.print("Valid port syntax -- ");
		if(!urlVal.isValid("http://google.com:80")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Invalid port syntax -- ");
		if(urlVal.isValid("http://google.com::80")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("No port number following : -- ");
		if(urlVal.isValid("http://google.com:")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Letters following : -- ");
		if(urlVal.isValid("http://google.com:12a4")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Symbols following : -- ");
		if(urlVal.isValid("http://google.com:-124")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Valid port number = 0 -- ");
		if(!urlVal.isValid("http://google.com:0")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");

		System.out.print("Invalid port number = 65536 -- ");
		if(urlVal.isValid("http://google.com:0")){
			testFail = true;
			System.out.print("FAIL\n");
		} else System.out.print("PASS\n");


		System.out.println("");
		assertFalse(testFail);

	}

	public void testIsValid()
	{
		//Programming based testing

		int bugsFound = 0;

		System.out.println("  ****Programming based testing****");
		System.out.println("Testing with invalid URLs:");

		String[] urlSchemeFalse = {"http;://", "http", "http:://", "http:::"};
		String[] urlAuthorityFalse = {"www.fun", ".com", "!!!.google.com", "www.google.!!!"};
		String[] urlPortFalse = {":squid", ":1squid2", ":-2222", ":123456789"};
		String[] urlPathFalse = {"//bugs", "/bugs//", "/|bugs", "/b/u//g/s"};
		String[] urlPathOptionsFalse = {"//buttons", "/buttons///", "/buttons/?$&", "/b/u/tto//ns"};

		String[] urlSchemeTrue = {"http://", "http://", "", ""}; //code fails when https://, h3t://, or ftp:// are used
		String[] urlAuthorityTrue = {"www.google.com", "yahoo.com", "www.byte.us.com", "byte.au"};
		String[] urlPortTrue = {":80", ":8080", ":1234", ""};
		String[] urlPathTrue = {"/tic", "/tic/tac", "/tic~tac", ""};
		String[] urlPathOptionsTrue = {"/cake", "/cake?pie=100", "/search?p=cake+pie", "/search?q=valid+url+path+characters"};	   	


		System.out.println("Test Known False Scheme...");
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeFalse[i] + urlAuthorityTrue[j] + urlPortTrue[k] + urlPathTrue[l] + urlPathOptionsTrue[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);

							if ( myTest8 != false ) {
								bugsFound++;

								System.out.println("Bug found, expected false: " + myUrl);

							}
						}
					}
				}

			}
		}

		System.out.println("Test Known False Authority...");
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeTrue[i] + urlAuthorityFalse[j] + urlPortTrue[k] + urlPathTrue[l] + urlPathOptionsTrue[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);

							if ( myTest8 != false ) {
								bugsFound++;

								System.out.println("Bug found, expected false: " + myUrl);

							}
						}
					}
				}

			}
		}

		System.out.println("Test Known False Port...");
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeTrue[i] + urlAuthorityTrue[j] + urlPortFalse[k] + urlPathTrue[l] + urlPathOptionsTrue[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);

							if ( myTest8 != false ) {
								bugsFound++;

								System.out.println("Bug found, expected false: " + myUrl);

							}
						}
					}
				}

			}
		}

		System.out.println("Test Known False Path...");
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeTrue[i] + urlAuthorityTrue[j] + urlPortTrue[k] + urlPathFalse[l] + urlPathOptionsTrue[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);

							if ( myTest8 != false ) {
								bugsFound++;

								System.out.println("Bug found, expected false: " + myUrl);

							}
						}
					}
				}

			}
		}

		System.out.println("Test Known False Path Options/Queries...");
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeTrue[i] + urlAuthorityTrue[j] + urlPortTrue[k] + urlPathTrue[l] + urlPathOptionsFalse[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);

							if ( myTest8 != false ) {
								bugsFound++;

								System.out.println("Bug found, expected false: " + myUrl);

							}
						}
					}
				}

			}
		}
		System.out.println("Total bugs found: " + bugsFound);	   	
	}
}

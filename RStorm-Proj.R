hdata <- read.table('domainStorms.rtf', header = FALSE, col.names = paste0("V",seq_len(8)), fill = TRUE)
#checking changes.
list_iterator <- 1
newlist <- list()

inc <- function(x)
{
  eval.parent(substitute(x <- x + 1))
}

data_parser <- function(dataframe){
  head <- 1
  max_wind_speed <- 0
  min_pressure <- 1020
  
  #encounter header
  while(as.character(dataframe[head,"V1"]) == 'start') {
    n_entries <- dataframe[head,"V2"]
    row_name <- paste(dataframe[head,"V3"], dataframe[head,"V4"], dataframe[head,"V5"], sep = "/")
    #interate through all entries of a storm
    for(row in head+1:n_entries){
      #check each entry for new potential wind speed max
      new_wind_speed <- as.numeric(as.character(dataframe[row,"V3"]))
      new_pressure <- as.numeric(as.character(dataframe[row,"V4"]))
     #update max wind speed
      if(new_wind_speed > max_wind_speed){
        max_wind_speed <- new_wind_speed
      }
      #update minimum pressure
      if(new_pressure < min_pressure){
        min_pressure <- new_pressure
      }
    }
    
    new_row <- data.frame(row_title = row_name, max_wind = max_wind_speed, min_pressure = min_pressure)
    print(list_iterator)
    print(new_row)
    newlist[[list_iterator]] <- new_row
    max_wind_speed <- 0
    min_pressure <- 1020
    inc(list_iterator)
    head <- head + n_entries + 1
    if(is.na(dataframe[head,"V1"])){
      print('end of file reached')
      break
    }
  }
  new_dataframe <- do.call(rbind.data.frame, newlist)
  return(new_dataframe)
}


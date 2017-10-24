hdata <- read.table('traj_1981.txt', header = FALSE, col.names = paste0("V",seq_len(8)), fill = TRUE)


data_parser <- function(dataframe){
  head <- 1
  while(as.character(dataframe[head,"V1"]) == 'start') {
    n_entries <- dataframe[head,"V2"]
    for(row in head+1:n_entries){
      lon <- as.numeric(as.character(dataframe[row,"V1"]))
      lat <- as.numeric(as.character(dataframe[row,"V2"]))
      lon <- (360 - lon)
      if( lat > 25 & lat < 27 & lon > 79 & lon < 81){
        print(paste('check passed: ',lat, lon))
        break
      }
    }
    head <- head + n_entries + 1
    if(is.na(dataframe[head,"V1"])){
      print('end of file reached')
      break
    }
  }
}

